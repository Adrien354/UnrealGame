// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Kismet/GameplayStatics.h>
#include "Components/ArrowComponent.h"
#include "Wind_CPP.generated.h"

class AExampleChar;

UCLASS()
class ONLYEXAMPLE_API AWind_CPP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWind_CPP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//sets wind direction
	void SetWindDirection();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ZRotation")
	float ZRotation;

	UPROPERTY()
	AExampleChar* MyExampleCharRef;

	UPROPERTY(BlueprintReadWrite)
	UArrowComponent* WindDirectionArrow;
};
