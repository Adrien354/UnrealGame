// Individual developer Adrian Filipek.


#include "F_Parent.h"

#include "ContentBrowserItemData.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"
#include "OnlyExample/ExampleChar.h"
#include "Kismet/GameplayStatics.h"
#include "Logging/StructuredLog.h"

// Sets default values
AF_Parent::AF_Parent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 5.0f;

}

// Called when the game starts or when spawned
void AF_Parent::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(false);

	MyExampleChar = Cast<AExampleChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	SpawnTransform = FTransform(GetActorRotation(), FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 50.f));
}

// Called every frame
void AF_Parent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FireSystem();
	CookFood();
}

void AF_Parent::FireSystem()
{
	if (FireSpotData.bIsBurning) {
		FireSpotData.EstimatedMinutesBurning -= 1;
		UE_LOG(LogTemp, Warning, TEXT("Time left: %i"), FireSpotData.EstimatedMinutesBurning);
	}
	else {
		SetActorTickEnabled(false);
		return;
	}

	if (FireSpotData.EstimatedMinutesBurning <= 0) {
		FireSpotData.EstimatedMinutesBurning = 0;
		FireSpotData.bIsBurning = false;
		MyExampleChar->bIsStartFireActive = false;
	}
}

void AF_Parent::CookSystem(AActor* BaseItem, FItemFoodData FoodDataStruct)
{
	if(FireSpotData.bIsBurning == false)
		return;

	FoodData = FoodDataStruct;
	FireSpotData.bIsCooking = true;
	TimeToCook = FoodDataStruct.TimeToCook;
	if(BaseItem)
	{
		SpawnedActor = GetWorld()->SpawnActor(BaseItem->GetClass(), &SpawnTransform);
		SpawnedActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	}
}

void AF_Parent::CookFood()
{
	if(FoodData.CookedItem == nullptr || FireSpotData.bIsCooking == false)
		return;

	TArray<AActor*> tempChildActors;
	this->GetAttachedActors(tempChildActors, true);
	if(tempChildActors.Num() == 0 || FoodData.bCanBeCooked == false){
		FoodData = FItemFoodData();
		TimeToCook = 0;
		FireSpotData.bIsCooking = false; 
		MyExampleChar->bIsStartFireActive = false;
		SpawnedActor=nullptr;
		return;
	}	
	
	UE_LOGFMT(LogTemp, Log, "Time to cook food: {0}", TimeToCook);

	TimeToCook -= 1;
	
	if(TimeToCook < 0)
	{
		if(FoodData.CookedItem)
		{
			SpawnedActor->Destroy();
			SpawnedActor = GetWorld()->SpawnActor(FoodData.CookedItem, &SpawnTransform);
			SpawnedActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
			FoodData.bCanBeCooked = false;
		}

		TimeToCook = FoodData.TimeToCook;
	}
}



