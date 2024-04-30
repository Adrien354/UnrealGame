// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <OnlyExample/ExampleChar.h>
#include "Components/ActorComponent.h"
#include "AC_Calories.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ONLYEXAMPLE_API UAC_Calories : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_Calories();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void CalculatePlayerCalories();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AExampleChar* MyExampleChar_ref;
};
