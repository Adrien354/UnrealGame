// Fill out your copyright notice in the Description page of Project Settings.

/** 
*This component calculates calories loose based on activities
* It is used to show the real needs of men
**/


#include "AC_Calories.h"

// Sets default values for this component's properties
UAC_Calories::UAC_Calories()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 0.5f;
}


// Called when the game starts
void UAC_Calories::BeginPlay()
{
	Super::BeginPlay();

	//Cast to my example character
	MyExampleChar_ref = Cast<AExampleChar>(GetOwner());
}


// Called every frame
void UAC_Calories::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CalculatePlayerCalories();
}

void UAC_Calories::CalculatePlayerCalories() {
	if (!MyExampleChar_ref->bIsSleeping) {
		if (MyExampleChar_ref->GetVelocity().Size() > 0.0) {
			if (MyExampleChar_ref->bIsSprinting) {
				MyExampleChar_ref->CaloriesLooseMultiplier = 0.625f;
			}
			else {
				MyExampleChar_ref->CaloriesLooseMultiplier = 0.375f;
			}
		}
		else MyExampleChar_ref->CaloriesLooseMultiplier = 0.25f;
	}

	MyExampleChar_ref->Calories -= MyExampleChar_ref->CaloriesLooseMultiplier;
	MyExampleChar_ref->Calories = FMath::Clamp(MyExampleChar_ref->Calories, 0.0f, MyExampleChar_ref->maxCalories);
}
