// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EItemCategory : uint8
{

	Food = 0 UMETA(DisplayName = "Food"),
	Drink = 1 UMETA(DisplayName = "Drink"),
	Weapons = 2 UMETA(DisplayName = "Weapons"),
	Clothing = 3 UMETA(DisplayName = "Clothing"),
	Heat = 4 UMETA(DisplayName = "Heat"),

};
