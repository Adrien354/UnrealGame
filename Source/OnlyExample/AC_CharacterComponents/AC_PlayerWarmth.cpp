// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_PlayerWarmth.h"

// Sets default values for this component's properties
UAC_PlayerWarmth::UAC_PlayerWarmth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 5.f;
	// ...
}


// Called when the game starts
void UAC_PlayerWarmth::BeginPlay()
{
	Super::BeginPlay();

	//Casting to main character
	MyExampleCharRef = Cast<AExampleChar>(GetOwner());
	
}


// Called every frame
void UAC_PlayerWarmth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	float WarmthMultiplied = MyExampleCharRef->Warmth + (MyExampleCharRef->FeelsLikeTemp * WarmthMultiplier);

	if (MyExampleCharRef->FeelsLikeTemp <= 0.f && WarmthMultiplied < 0.5) {
		MyExampleCharRef->Warmth = 0.f;
	}
	else {
		MyExampleCharRef->Warmth = FMath::Clamp(FMath::Abs(WarmthMultiplied), 0.f, 100.f);
	}
}

