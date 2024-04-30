// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Kismet/GameplayStatics.h>
#include "GameFramework/Actor.h"
#include "TimeCounter.generated.h"

class AExampleChar;

UCLASS()
class ONLYEXAMPLE_API ATimeCounter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimeCounter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Character reference
	class AExampleChar* MyExampleCharRef;

#pragma region /** Time */
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Time")
	int currentMinutes = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Time")
	FString timeString = FString(TEXT(""));

public:

	//count time that player survived
	UFUNCTION(BlueprintCallable)
	void CountTimeSurvived2();

	//Get in-game time of the day
	UFUNCTION(BlueprintCallable)
	void GetTimeOfDay();
#pragma endregion
};
