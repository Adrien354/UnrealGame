// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "ClothesCategory.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EItemClothesCategory : uint8
{
	Jacket = 0b0000 UMETA(DisplayName = "Jacket"),
	Sweater = 0b0001 UMETA(DisplayName = "Sweater"),
	Bottom = 0b0010 UMETA(DisplayName = "Bottom"),
	Shoe = 0b0100 UMETA(DisplayName = "Shoe"),
	Hat = 0b1000 UMETA(DisplayName = "Hat"),
	Socks = 0b0011 UMETA(DisplayName = "Socks"),
};
