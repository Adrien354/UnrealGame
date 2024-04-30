// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HeatCategory.h"
#include "HeatData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct ONLYEXAMPLE_API FHeatData
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Minutes Burning", MakeStructureDefaultValue = 0))
	int MinutesBurning;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Category of heat", MakeStructureDefaultValue = 0))
	TEnumAsByte<EHeatCategory> Category;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Bonus Starting Fire", MakeStructureDefaultValue = 0))
	float BonusStartingFire;

	/** Heat that is generated from the item */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Generated Heat", MakeStructureDefaultValue = 0))
	float GeneratedHeat;
	
	FHeatData();
	~FHeatData();
};
