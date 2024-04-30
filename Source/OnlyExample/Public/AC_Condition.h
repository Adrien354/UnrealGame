// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlyExample/ExampleChar.h"
#include "ItemCategory.h"
#include "Components/ActorComponent.h"
#include "AC_Condition.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ONLYEXAMPLE_API UAC_Condition : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_Condition();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Character reference
	AExampleChar* MyExampleCharRef = nullptr;

	//Function for updating condition of items
	UFUNCTION(BlueprintCallable)
	void UpdateConditionOfItems();

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
	double ConditionLooseMultiplier = 1.f;

};
