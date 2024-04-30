// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClothesCategory.h"
#include "Engine/UserDefinedStruct.h"
#include "ItemClothingData.generated.h"

 /** Struct for clothes items */
USTRUCT(BlueprintType)
struct FItemClothingData
{
	GENERATED_BODY()
public:
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Warmth Bonus", MakeStructureDefaultValue = "0.000000"))
	double WarmthBonus;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Actual warmth bonus", MakeStructureDefaultValue = "0.000000"))
	double ActualWarmthBonus;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "bIsWearing", MakeStructureDefaultValue = "False"))
	bool bIsWearing;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "CategoryOfClothes"))
	TEnumAsByte<EItemClothesCategory> CategoryOfClothes;
};

