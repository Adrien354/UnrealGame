// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OnlyExample/ExampleChar.h"
#include "AC_PlayerWarmth.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ONLYEXAMPLE_API UAC_PlayerWarmth : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_PlayerWarmth();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Character reference
	AExampleChar* MyExampleCharRef = nullptr;

	/** what value multiply warmth*/
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
	double WarmthMultiplier = 0.2f;

};
