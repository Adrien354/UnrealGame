// Fill out your copyright notice in the Description page of Project Settings.;


#include "AC_FatigueSystem.h"

// Sets default values for this component's properties
UAC_FatigueSystem::UAC_FatigueSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAC_FatigueSystem::BeginPlay()
{
	Super::BeginPlay();

	//Cast to ExampleChar
	MyExampleChar_ref = Cast<AExampleChar>(GetOwner());
}


// Called every frame
void UAC_FatigueSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CalculatePlayerFatigue(DeltaTime);
}

void UAC_FatigueSystem::CalculatePlayerFatigue(float deltaTime)
{
	if (!MyExampleChar_ref->bIsSleeping) {
		if (MyExampleChar_ref->GetVelocity().Size() > 0.f) {
			if (MyExampleChar_ref->bIsSprinting) {
				FatigueMultiplier = 3.5f;
			}
			else {
				FatigueMultiplier = 2.0f;
			}
		}
		else {
			FatigueMultiplier = 0.5;
		}
	}
	else {
		if (MyExampleChar_ref->Fatigue >= 100.f) {
			MyExampleChar_ref->StopSleep();
		}
	}

	MyExampleChar_ref->Fatigue = FMath::Clamp(MyExampleChar_ref->Fatigue - (FatigueLoose * FatigueMultiplier * deltaTime), 0.f, 100.f);
}

