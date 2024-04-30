// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OnlyExample/ExampleChar.h"
#include "AC_Temperature.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ONLYEXAMPLE_API UAC_Temperature : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_Temperature();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//character reference
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AExampleChar* MyExampleChar_ref = nullptr;

	//Calculate the strength of wind
	UFUNCTION()
	void SetWindStrength();
	
	//Calculate world temperature based on wind strength
	void SetWorldTemp();

};
