// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemCategory.h"
#include "ItemFoodData.h"
#include "ItemClothingData.h"
#include "HeatData.h"
#include "WeaponData.h"
#include "ItemData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct ONLYEXAMPLE_API FItemData
{
	GENERATED_BODY()
public:
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Name"))
	FString Name;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Description"))
	FString Description;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Base Item"))
	TObjectPtr<AActor> ItemClass;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Details"))
	FString Details;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Image", MakeStructureDefaultValue = "None"))
	TObjectPtr<UTexture2D> Image;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Category", MakeStructureDefaultValue = "NewEnumerator0"))
	TEnumAsByte<EItemCategory> Category;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Condition", MakeStructureDefaultValue = "0.000000"))
	double Condition;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Decay", MakeStructureDefaultValue = "0.000000"))
	double Decay;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Weight", MakeStructureDefaultValue = "0.000000"))
	double Weight;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "bCanBeStacked", MakeStructureDefaultValue = "False"))
	bool bCanBeStacked;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Food data struct", MakeStructureDefaultValue = "(Calories=0,bIsEatable=False)"))
	FItemFoodData FoodDataStruct;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Clothing data struct", MakeStructureDefaultValue = "(WarmthBonus=0.000000,ActualWarmthBonus=0.000000,bIsWearing=False,CategoryOfClothes=Jacket)"))
	FItemClothingData ClothingDataStruct;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Heat data struct", MakeStructureDefaultValue = "(MinutesBurning=0,Category=FireStarter,BonusStartingFire=0.000000)"))
	FHeatData HeatDataStruct;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Weapon data struct", MakeStructureDefaultValue = "(Damage=0,CriticalHitChance=0.000000)"))
	FWeaponData WeaponDataStruct;


	FItemData();
	~FItemData();
};
