// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EHeatCategory : uint8
{

	FireStarter UMETA(DisplayName = "FireStarter"),
	Tinder UMETA(DisplayName = "Tinder"),
	Fuel UMETA(DisplayName = "Fuel"),
	Accelerant UMETA(DisplayName = "Accelerant"),

};
