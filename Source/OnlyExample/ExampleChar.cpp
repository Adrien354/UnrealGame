// Fill out your copyright notice in the Description page of Project Settings.

#include "ExampleChar.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include "OnlyExample/Widgets/FireSpotsFeaturesWidget.h"
#include "AC_CharacterComponents/AC_PlayerHealth.h"
#include "../../../../UE_5.3/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "../../../../UE_5.3/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "MyInputConfigData.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Widgets/Fire/FireSpotAddFuelWidget.h"

// Sets default values
AExampleChar::AExampleChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    Warmth = 100.f;

}

// Called when the game starts or when spawned
void AExampleChar::BeginPlay()
{
	Super::BeginPlay();



    //Set the stamina to the max value
    ActualStaminaInSeconds = StaminaInSeconds;

    //Get the character capsule
    Capsule = GetCapsuleComponent();

    

    //sprinting Timeline
    FOnTimelineFloat ProgressUpdate;
    ProgressUpdate.BindUFunction(this, FName("SprintUpdate"));

    //Call a function if the timeline ended playing
    FOnTimelineEvent FinishedEvent;
    FinishedEvent.BindUFunction(this, FName("SprintFinished"));

    //Add a curve for a smooth sprinting
    SprintingTimeline.AddInterpFloat(SprintingCurve, ProgressUpdate);
    SprintingTimeline.SetTimelineFinishedFunc(FinishedEvent); //Set function to call if sprint timeline ends playing

    //Casting to TimeCounter Actor
    TimeCounter_ref = Cast<ATimeCounter>(AExampleChar::Capsule->GetChildComponent(2));

    //get camera component
    FPSCamera = FindComponentByClass<UCameraComponent>();

    //directional light reference
    if(DirectionalLightRef == nullptr)
        DirectionalLightRef = Cast<ADirectionalLight>(UGameplayStatics::GetActorOfClass(GetWorld(), ADirectionalLight::StaticClass()));

    //AC_PlayerHealth reference
    if (!PlayerHealthComp) {
        UActorComponent* Component = GetComponentByClass(UAC_PlayerHealth::StaticClass());
        PlayerHealthComp = Cast<UAC_PlayerHealth>(Component);
    }

    PlayerHealthComp->TakeDamageFromFreezing(.002f);
}

// Called every frame
void AExampleChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    //Sprint system tick function
    SprintTickFunction(DeltaTime);

    //Function to detect hiding from wind
    IsObjectOppositeDirectionToWind();
}

// Called to bind functionality to input
void AExampleChar::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    // Get the player controller
    PC = Cast<APlayerController>(GetController());

    // Get the local player subsystem
    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
    // Clear out existing mapping, and add our mapping
    Subsystem->ClearAllMappings();
    Subsystem->AddMappingContext(InputMapping, 0);

    UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);

    PEI->BindAction(InputActions->InputMove, ETriggerEvent::Triggered, this, &AExampleChar::Move);
    PEI->BindAction(InputActions->InputLook, ETriggerEvent::Triggered, this, &AExampleChar::Look);
    PEI->BindAction(InputActions->InputCrouch, ETriggerEvent::Triggered, this, &AExampleChar::Crouching);
    PEI->BindAction(InputActions->InputSprint, ETriggerEvent::Triggered, this, &AExampleChar::Sprint);
    PEI->BindAction(InputActions->InputSprint, ETriggerEvent::Completed, this, &AExampleChar::StopSprint);
    PEI->BindAction(InputActions->InputSprint, ETriggerEvent::Completed, this, &AExampleChar::SetStamina);
}


void AExampleChar::SprintTickFunction(float deltaTime) {
    SprintingTimeline.TickTimeline(deltaTime);
    CrouchingTimeline.TickTimeline(deltaTime);

    if (ActualStaminaInSeconds <= 0.f && bIsSprinting == true) {
        StopSprint();
        ActualStaminaInSeconds = 0.f;
        bNotHaveStamina = true;
    }

    if (bIsSprinting == true && ActualStaminaInSeconds >= 0.f) {

        ActualStaminaInSeconds -= StaminaLoseSpeed * deltaTime;
    }
    else {

        if (ActualStaminaInSeconds >= StaminaInSeconds) {
            ActualStaminaInSeconds = StaminaInSeconds;
        }
        else {
            ActualStaminaInSeconds += StaminaGainSpeed * deltaTime;
        }
    }
}


/** Setting condition after taking some damage */
void AExampleChar::TakeDamage(double value)
{
    this->Condition -= value;

    if (Condition <= 0.f) {
        //call function die if player has no health points;
        Die();
    }

    Condition = FMath::Clamp(Condition, 0.0f, 100.f); //clamp value so player health cannot be more than 100 and less than 0.
}

/*
    * Sets player condition after e.g. eating, sleeping etc.
    * Adds amount given in the parameter of the function.
*/
void AExampleChar::RestoreCondition(double value)
{

    this->Condition += value;

    Condition = FMath::Clamp(Condition, 0.0f, 100.f); //clamp value so player health cannot be more than 100 and less than 0.

}

//Handle Move
void AExampleChar::Move(const FInputActionValue& Value)
{
    if (Controller != nullptr && !bInventoryActive)
    {
        const FVector2D MoveValue = Value.Get<FVector2D>();
        MovingValue = MoveValue;
        const FRotator MovementRotation(0, Controller->GetControlRotation().Yaw, 0);

        // Forward/Backward direction
        if (MoveValue.Y != 0.f)
        {
            // Get forward vector
            const FVector Direction = GetActorForwardVector();

            AddMovementInput(Direction, MoveValue.Y);
        }

        // Right/Left direction
        if (MoveValue.X != 0.f)
        {
            // Get right vector
            const FVector Direction = GetActorRightVector();

            AddMovementInput(Direction, MoveValue.X);
            StopSprint();
        }

        if (MovingValue.Y < 0.f || MovingValue.X != 0.f) {
            StopSprint();

        }
    }
}


//Handle Look
void AExampleChar::Look(const FInputActionValue& Value)
{
    if (Controller != nullptr && !bInventoryActive)
    {
        const FVector2D LookValue = Value.Get<FVector2D>();

        if (LookValue.X != 0.f)
        {
            AddControllerYawInput(LookValue.X);
        }

        if (LookValue.Y != 0.f)
        {
            AddControllerPitchInput(LookValue.Y);
        }
    }
}

//Handle Crouching
void AExampleChar::Crouching(const FInputActionValue& Value) {
    if (Controller != nullptr && !bInventoryActive) {
        if (!ACharacter::bIsCrouched) {
            StopSprint();
            bIsCrouching = true;
            bStartedCrouching = false;
            ACharacter::Crouch();
        }
        else {
            StopSprint();
            bStartedCrouching = false;
            bIsCrouching = false;
            ACharacter::UnCrouch();
        }
    }
}

//Handle Sprint and Stamina
void AExampleChar::Sprint()
{
    if (Controller != nullptr && MovingValue.Y > 0.0f && !(MovingValue.X != 0.f) &&
        ActualStaminaInSeconds > 0.f && !bNotHaveStamina && bIsCrouching==false && !ACharacter::bIsCrouched) 
    {
        
        SprintingTimeline.Play();
        bIsSprinting = true;

    }
}

void AExampleChar::StopSprint()
{
    if (Controller != nullptr) {

        //Reverse animation if player realeases button
        SprintingTimeline.Reverse();
        bIsSprinting = false;
    }
}

void AExampleChar::SetStamina()
{
    bNotHaveStamina = false;
}

void AExampleChar::SprintUpdate(float alpha)
{
    //Lerp from walk speed to sprint speed
    //To make the smooth transition between sprinting and walking
    float newSprintSpeed = FMath::Lerp(300, 600, alpha);
    CharacterMovement->MaxWalkSpeed = newSprintSpeed;
}

void AExampleChar::SprintEnd()
{

}


//Wind implemantation
void AExampleChar::IsObjectOppositeDirectionToWind()
{
    /** reference to actor component that was hit by raycast */
    FHitResult OutHit;

    /** Get Camera position to start raycast from the camera point */
    FVector StartLocation = FVector(FPSCamera->GetComponentLocation());

    /** Get location that raycast should end */
    FVector EndLocation = FVector((-WindObjectRef->WindDirectionArrow->GetForwardVector()) * (DistanceToHideFromWind * 2) + StartLocation);

    /** radius of the sphere that will check the actor */
    float SphereRadius = 5.f;

    //Raycast to check if wall is in front of player
    bIsWallInFront = GetWorld()->SweepSingleByChannel(OutHit, StartLocation, EndLocation,
        FQuat::Identity, ECC_Visibility , FCollisionShape::MakeSphere(SphereRadius));

    /** Get location that second raycast should end  */
    FVector EndLocation2 = FVector((-WindObjectRef->WindDirectionArrow->GetForwardVector()) * (DistanceToHideFromWind * 3));

    /** Get the location 400 hundred units above so it raycasts at some angle */
    FVector EndFinalLocation = FVector(EndLocation2.X, EndLocation2.Y, EndLocation2.Z + 400.f);

    //Raycast to check if wall or other object is at some angle and distance from player
    bIsWall45DegreesAbove = GetWorld()->SweepSingleByChannel(OutHit, (StartLocation + FVector(0.f, 0.f, -30.f)),
        (EndFinalLocation + StartLocation),FQuat::Identity, ECC_Visibility, FCollisionShape::MakeSphere(SphereRadius));

}

    /*
     * Temperature implementation
    */

//set feels like temperature for player
void AExampleChar::SetFeelsLikeVariable()
{
    BonusFromClothing = 0.f;
    if (InventoryList.IsEmpty()) {
        FeelsLikeTemp = WorldTemp;
        return;
    }
    else {
        int length = InventoryList.Num();

        for (int i = 0; i < length; i++)
        {
            if (InventoryList[i].Category == EItemCategory::Clothing && InventoryList[i].ClothingDataStruct.bIsWearing) {
                /** Get condition divided by 100 to get values from 0.0 to 1.0 */
                float ConditionTemp = InventoryList[i].Condition / 100.f;

                /** Get warmth bonus based on clothing condition and primary warmth */
                float WarmthBonusTemp = InventoryList[i].ClothingDataStruct.WarmthBonus * ConditionTemp;

                /** Add bonus from clothing to previous variable */
                float FinalBonusFromClothing = BonusFromClothing + WarmthBonusTemp;

                /** Sum of bonuses from clothing  */
                BonusFromClothing = FinalBonusFromClothing;
            }
        }

        /** set the feels like temperature with clothes put on */
        FeelsLikeTemp = WorldTemp + BonusFromClothing;
        return;
    }

}

void AExampleChar::Searching()
{
    SearchingUI = CreateWidget<UW_SearchingUI>(PC, SearchingUIClass);
    check(SearchingUI);

    bIsSearching = true;
    bInventoryActive = true;

    //Add widget to player screen
    SearchingUI->AddToPlayerScreen();

    //Set mode for UI and Game
    PC->SetInputMode(FInputModeGameAndUI());

}

void AExampleChar::StopSearching() 
{
    //check if serachingUI is valid
    if (!SearchingUI)
        return;

    //Remove widget from player screen
    SearchingUI->RemoveFromParent();
    SearchingUI = nullptr;

    //Set input mode back to game
    PC->SetInputMode(FInputModeGameOnly());

    //set variables to default state
    bInventoryActive = false;
    bIsSearching = false;

    //set actor traced to null pointer
    ActorTraced = nullptr;
}

//MUST BE IMPLEMENTED WHEN I FINISH WITH HEALTH SYSTEM!!!!
/*
* This function is called when player looses his condition(health)
* It displays death ui and ends the game 
*/
void AExampleChar::Die()
{

}

/*
 * Used to AddCalories from every actor or object
*/
void AExampleChar::AddCalories(float value)
{
	Calories += value;
	Calories = FMath::Clamp(Calories, 0.f, maxCalories);
}

/*
 * Create Fire Spot Cook Widget
 */
void AExampleChar::CreateFireSpotCookWidget() {
    //Creates widget and checks if its valid
    if(FireSpotCookWidget == nullptr)
        FireSpotCookWidget = CreateWidget<UFireSpotCookWidget>(PC, FireSpotCookWidgetClass);

    check(FireSpotCookWidget);

    //Sets variables
    bInventoryActive = true;
    bIsSearching = true;

    FireSpotCookWidget->AddToPlayerScreen();

    //Show mouse cursor
    PC->bShowMouseCursor = true;
    ActorTraced = nullptr;
}

void AExampleChar::RemoveFireSpotCookWidget()
{
    //validation
    if(FireSpotCookWidget == nullptr)
        return;

    //unset variables
    bInventoryActive = false;
    bIsSearching = false;

    PC->bShowMouseCursor = false;
    PC->SetInputMode(FInputModeGameOnly());
    
    //Remove from player screen
    FireSpotCookWidget->RemoveFromParent();
    FireSpotCookWidget = nullptr;
}

void AExampleChar::CreateFireSpotAddFuelWidget()
{
    //Creates widget and checks if its valid
    if(FireSpotAddFuelWidget == nullptr)
        FireSpotAddFuelWidget = CreateWidget<UFireSpotAddFuelWidget>(PC, W_FireSpotAddFuel);

    check(FireSpotAddFuelWidget);

    //Sets variables
    bInventoryActive = true;
    bIsSearching = true;

    FireSpotAddFuelWidget->AddToPlayerScreen();

    //Show mouse cursor
    PC->bShowMouseCursor = true;
    ActorTraced = nullptr;
}

void AExampleChar::RemoveFireSpotAddFuelWidget()
{
    //validation
    if(FireSpotAddFuelWidget == nullptr)
        return;

    //unset variables
    bInventoryActive = false;
    bIsSearching = false;

    PC->SetInputMode(FInputModeGameOnly());
    PC->bShowMouseCursor = false;
    
    //Remove from player screen
    FireSpotAddFuelWidget->RemoveFromParent();
    FireSpotAddFuelWidget = nullptr;
}

