// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeCounter.h"
#include "ExampleChar.h"

// Sets default values
ATimeCounter::ATimeCounter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATimeCounter::BeginPlay()
{
	Super::BeginPlay();

	MyExampleCharRef = Cast<AExampleChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
}

// Called every frame
void ATimeCounter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CountTimeSurvived2();
	GetTimeOfDay();
}

void ATimeCounter::CountTimeSurvived2()
{
	MyExampleCharRef->Minutes = ((FMath::RoundToInt(UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld())) - currentMinutes) / 5);

	if (MyExampleCharRef->Minutes >= 60) {
		MyExampleCharRef->Hours += 1;
		MyExampleCharRef->Minutes %= 60;
		currentMinutes = FMath::TruncToInt(UKismetSystemLibrary::GetGameTimeInSeconds(GetWorld()));
	}

	if (MyExampleCharRef->Hours == 24) {
		MyExampleCharRef->Days += 1;
		MyExampleCharRef->Hours = 0;
	}
}

void ATimeCounter::GetTimeOfDay() 
{
	if (MyExampleCharRef->bIsAM) {
		timeString = FString::Printf(TEXT("Hour: %d Minutes: %d"), FMath::FloorToInt(MyExampleCharRef->TempTimeOfDay), FMath::RoundToInt((MyExampleCharRef->TempTimeOfDay - FMath::FloorToInt(MyExampleCharRef->TempTimeOfDay)) * 60));
	}
	else {
		float dayTime = FMath::GetMappedRangeValueUnclamped(FVector2D(0.f, 12.f), FVector2D(12.f, 0.f), MyExampleCharRef->TempTimeOfDay);
		if (FMath::FloorToInt(dayTime) == 0) {
			timeString = FString::Printf(TEXT("Hour: 12 Minutes: %d"), FMath::RoundToInt((dayTime-FMath::Floor(dayTime)) * 60));
		}
		else {
			timeString = FString::Printf(TEXT("Hour: %d Minutes: %d"),FMath::FloorToInt(dayTime), FMath::RoundToInt((dayTime - FMath::Floor(dayTime)) * 60));
		}
	}
}

