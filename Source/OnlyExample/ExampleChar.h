// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "TimeCounter.h"
#include "ItemData.h"
#include "Widgets/W_SearchingUI.h"
#include "Camera/CameraComponent.h"
#include "Wind/Wind_CPP.h"
#include "Engine/DirectionalLight.h"
#include "Components/TimelineComponent.h"
#include "ExampleChar.generated.h"

class AF_Parent;
class UCurveFloat;
class UCapsuleComponent;
class UCameraComponent;
class ADirectionalLight;
class UAC_PlayerHealth;

UCLASS()
class ONLYEXAMPLE_API AExampleChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AExampleChar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



#pragma region /** General */

	// Indicates if the W key is pressed
	UPROPERTY(BlueprintReadWrite, Category = "Input")
	bool IsWPressed;

	// Reference for player controller
	UPROPERTY(BlueprintReadWrite)
	APlayerController* PC = nullptr;

	// Camera component 
	UPROPERTY(BlueprintReadWrite)
	UCameraComponent* FPSCamera;
	UFUNCTION()
	void SprintTickFunction(float deltaTime);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "General")
	class UAC_PlayerHealth* PlayerHealthComp;

#pragma endregion

#pragma region /** Input */
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UMyInputConfigData* InputActions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	bool bIsCrouching = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	bool bStartedCrouching = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UCapsuleComponent* Capsule;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	FVector2D MovingValue = FVector2D(0, 0);

	TObjectPtr<class UCharacterMovementComponent> CharacterMovement = GetCharacterMovement();

#pragma endregion

//Time Implementation
#pragma region /** Time */
public:
	//Time Survived
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Time")
	int Minutes;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Time")
	int Hours;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Time")
	int Days;

	//Property for speeding time
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Time")
	int MinutesMultiplier;

	//TimeCounter Actor ref
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Okej")
	ATimeCounter* TimeCounter_ref;
	
	//Actual Time in game
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Time")
	float ActualTime = 0.f;
	
	//Temporary time
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Time")
	float TempTimeOfDay;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Time")
	bool bIsAM;

#pragma endregion

	/** 
	*this region is made to contain human needs e.g. Hunger,Thirst etc.
	**/
	
#pragma region /** HumanNeeds */

	//Player calories left
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Hunger")
	float Calories = 100.f;

	/** max player calories */
	UPROPERTY(BlueprintReadOnly, Category = "Hunger")
	double maxCalories = 3000.f;

	//Calorie loose amount
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Hunger")
	float CaloriesLooseMultiplier = 0.25f;

	/** Add calories to player */
	UFUNCTION(BlueprintCallable)
	void AddCalories(float value);

#pragma endregion

#pragma region /** Sleep */

	//boolean isSleeping
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sleep")
	bool bIsSleeping;

	//Functions
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void StopSleep();

#pragma endregion

	/**
	* Variables and functions declarations for Player Condition(health)
	* this region is for declaring variables for player condition implementation
	**/

#pragma region /** Condition */

	/** health of the player */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Condition")
	double Condition = 100.f;

public:
	/** Decreases condition of the player using given value */
	UFUNCTION(BlueprintCallable)
	void TakeDamage(double value);

	/** Increases condition of the player using given value */
	UFUNCTION(BlueprintCallable)
	void RestoreCondition(double value);

#pragma endregion

#pragma region /** Fatigue */

	//Fatigue value from 100 - 0.
	//If 0 you are exhausted
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Fatigue = 100.f;

#pragma endregion

public:
	// Handle move input
	void Move(const FInputActionValue& Value);

	// Handle look input
	void Look(const FInputActionValue& Value);

	//Handle crouch input
	void Crouching(const FInputActionValue& Value);

	//Handle sprint input
	void Sprint();

	//Handle stop sprint input
	void StopSprint();

	//Handle Stamina
	void SetStamina();


#pragma region /** Stamina */
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stamina")
	float StaminaInSeconds = 5.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float ActualStaminaInSeconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float StaminaLoseSpeed = 0.3f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	float StaminaGainSpeed = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	bool bIsSprinting;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	bool bNotHaveStamina = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	UCurveFloat* SprintingCurve = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	UCurveFloat* CrouchCurve = nullptr;

public:
	FTimeline SprintingTimeline;
	FTimeline CrouchingTimeline;

	UFUNCTION()
	void SprintUpdate(float alpha);

	UFUNCTION()
	void SprintEnd();
#pragma endregion

#pragma region /** Inventory */

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	bool bInventoryActive = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	float TraceRadius = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	float TraceDistance = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	AActor* ActorTraced;

	/** array of items in inventory */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Inventory")
	TArray<FItemData> InventoryList;


#pragma endregion

	/**
	* Wind system made by me to simulate wind direction and windchill
	**/

#pragma region /** Wind */

	///Properties

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Wind")
	AWind_CPP* WindObjectRef;

	//Strength of the wind to determine how cold it is
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Wind")
	float WindStrength;

	//just a windchill
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Wind")
	float WindChill;

	//This contains a distance to the wall that you can hide when it's windy
	//If you are close to wall it will lower windchill
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Wind")
	float DistanceToHideFromWind = 150.f;

	//Stores windchill temporary value
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Wind")
	float WindChill_Temp;

	//boolean to check if wall is in front of your player
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Wind")
	bool bIsWallInFront;

	//boolean for checking if wall is 45 degrees above your player to make more realistic wind system
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Wind")
	bool bIsWall45DegreesAbove;

	///Functions

	//Checks if there is some object in opposite direction of wind direction according to the player location.
	//This helps describe if Player is protected from wind by some e.g. walls, corpses or another objects
	UFUNCTION(BlueprintCallable, Category = "Wind")
	void IsObjectOppositeDirectionToWind();

#pragma endregion

	/**
	 * This is the world and feels like temperature that affects player
	**/

#pragma region /** Temperature  */
	///Properties
	/** Player warmth values are in range 0 min 100 max */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Temperature")
	double Warmth = 100.f;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Temperature")
	ADirectionalLight* DirectionalLightRef;

	//Temperature of air
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Temperature")
	float AirTemp;
	//it is air temperature combined with windchill
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Temperature")
	float WorldTemp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Temperature")
	float BonusFromClothing = 0.f;

	/** Variable that stores player temperature that he is feeling */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Temperature")
	float FeelsLikeTemp;

	///Functions

	//Set player feels like temperature
	UFUNCTION(BlueprintCallable)
	void SetFeelsLikeVariable();

#pragma endregion


#pragma region /** Searching */

	///PROPERTIES
	/** indicates if player is searching e.g. drawer */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
	bool bIsSearching;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Search")
	TSubclassOf<class UW_SearchingUI> SearchingUIClass;

	UPROPERTY(BlueprintReadWrite, Category = "Search")
	class UW_SearchingUI* SearchingUI;

	///FUNCTIONS
	/** Search drawers cabinets etc. */
	UFUNCTION(BlueprintCallable, Category = "Search")
	void Searching();

	/** gives player a full control of body again and destroy searching widget */
	UFUNCTION(BlueprintCallable, Category = "Search")
	void StopSearching();

#pragma endregion

#pragma region /** Die */

	///PROPERTIES
	/** indicates if player is dead or not */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Die")
	bool bIsDead = false;

	///FUNCTIONS
	UFUNCTION(BlueprintCallable, Category = "Die")
	void Die();

#pragma endregion

#pragma region /** StartFire */

	///PROPERTIES
	/** indicates if player is starting fire */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Start Fire")
	bool bIsStartFireActive;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="StartFire")
	TObjectPtr<AF_Parent> FireSpot_BP;

#pragma endregion
	
#pragma region /** Cooking */

	/** Widget class to spawn for the heads-up display */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cooking")
	TSubclassOf<class UFireSpotCookWidget> FireSpotCookWidgetClass;

	/** The widget instance */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cooking")
	class UFireSpotCookWidget* FireSpotCookWidget;

	/** Create Fire Spot cook Widget*/
	UFUNCTION(BlueprintCallable, Category = "Cooking")
	void CreateFireSpotCookWidget();

	/** Remove Fire Spot cook Widget*/
	UFUNCTION(BlueprintCallable, Category = "Cooking")
	void RemoveFireSpotCookWidget();

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Cooking")
	TObjectPtr<class UFireSpotsFeaturesWidget> W_FireSpotFeatures;

#pragma endregion

#pragma region /** Add Fuel */

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "AddFuel")
	TSubclassOf<class UFireSpotAddFuelWidget> W_FireSpotAddFuel;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "AddFuel")
	class UFireSpotAddFuelWidget* FireSpotAddFuelWidget;

	/** Please add a variable description */
	UFUNCTION(BlueprintCallable, Category = "AddFuel")
	void CreateFireSpotAddFuelWidget();

	/** Remove Add Fuel widget and remove it from player screen */
	UFUNCTION(BlueprintCallable, Category = "AddFuel")
	void RemoveFireSpotAddFuelWidget();
	
#pragma endregion 
};


