// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemFoodData.generated.h"


/** Structure for food items */
USTRUCT(BlueprintType)
struct FItemFoodData
{
	GENERATED_BODY()
public:
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Calories", MakeStructureDefaultValue = "0"))
	double Calories;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "bIsEatable", MakeStructureDefaultValue = "False"))
	bool bIsEatable;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "bCanBeCooked"))
	bool bCanBeCooked = false;

	/** */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Time to cook"))
	float TimeToCook = 0.0f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Cooked Item Class"))
	TObjectPtr<UClass> CookedItem;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Burnt Item Class"))
	TObjectPtr<UClass> BurntItem;
};

