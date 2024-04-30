// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_Temperature.h"

// Sets default values for this component's properties
UAC_Temperature::UAC_Temperature()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 150.f;

}


// Called when the game starts
void UAC_Temperature::BeginPlay()
{
	Super::BeginPlay();

	//Get Player character reference
	MyExampleChar_ref = Cast<AExampleChar>(GetOwner());

	//Get directional light ref
	if(MyExampleChar_ref->DirectionalLightRef == nullptr)
		MyExampleChar_ref->DirectionalLightRef = Cast<ADirectionalLight>(UGameplayStatics::GetActorOfClass(GetWorld(), ADirectionalLight::StaticClass()));

	//Set some variables
	if (MyExampleChar_ref != nullptr) {
		SetWindStrength();
		SetWorldTemp();
	}
}


// Called every frame
void UAC_Temperature::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//call these functions per tick
	if (MyExampleChar_ref != nullptr) {
		SetWindStrength();
		SetWorldTemp();
	}

}

//Set strength of wind based on calculations
void UAC_Temperature::SetWindStrength() {
	if (FMath::RandRange(0.f, 1.f) <= 0.75f) {

		MyExampleChar_ref->WindStrength = FMath::Clamp(FMath::RandRange(MyExampleChar_ref->WindStrength + 10, FMath::Abs(MyExampleChar_ref->WindStrength - 10)), 0.1, 30.0);
		MyExampleChar_ref->WindChill = FMath::RandRange(0.2f,0.4f) * -MyExampleChar_ref->WindStrength;
	}
	else {
		MyExampleChar_ref->WindStrength = 0.f;
		MyExampleChar_ref->WindChill = 0.f;
	}

	MyExampleChar_ref->WindChill_Temp = MyExampleChar_ref->WindChill;
}

//Set world temperature
void UAC_Temperature::SetWorldTemp()
{
	//set AirTemp
	FVector2D InputRange = FVector2D(-90.f, 90.f);
	FVector2D OutputRange = FVector2D(FMath::RandRange(1.f, 1.25f) * -6.f, FMath::RandRange(.75f, 1.f) * -15.f);
	float DirLightRot = MyExampleChar_ref->DirectionalLightRef->GetActorRotation().Pitch;

	MyExampleChar_ref->AirTemp = FMath::GetMappedRangeValueUnclamped(InputRange, OutputRange, DirLightRot);

	//Set WorldTemp
	MyExampleChar_ref->WorldTemp = FMath::GetMappedRangeValueUnclamped(InputRange, OutputRange, DirLightRot) + MyExampleChar_ref->WindChill;

	MyExampleChar_ref->SetFeelsLikeVariable();
}

