// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponData.generated.h"

/** Data provided about weapon items */
USTRUCT(BlueprintType)
struct ONLYEXAMPLE_API FWeaponData
{
	GENERATED_BODY()
public:
	/** Damage that weapon is dealing */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Damage = 0;

	/** Chance of dealing a increased damage */
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CriticalHitChance = 0.f;

	FWeaponData();
	~FWeaponData();

};
