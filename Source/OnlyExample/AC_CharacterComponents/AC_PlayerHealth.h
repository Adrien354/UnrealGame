// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlyExample/ExampleChar.h"
#include "Components/ActorComponent.h"
#include "AC_PlayerHealth.generated.h"

class AExampleChar;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ONLYEXAMPLE_API UAC_PlayerHealth : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_PlayerHealth();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Player character reference */
	class AExampleChar* ExampleCharRef;

	/*
		* multiplier of damage while sleeping. It is done because while I'm sleeping I'm changing TickInterval ten times than it was
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Damage")
	float DamageMultiplier = 5.f;
#pragma region /** Starving */

	/** checks if player is starving and if he is take damage */
	UFUNCTION(BlueprintCallable)
	void TakeDamageFromStarving(float DamageAmount);

	/** damage from starving */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Damage")
	float DamageFromStarving = 0.0005f;

	/** Damage dealt used as a timer to check for how much time player is starving */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Damage")
	float DamageDealt = 0.0f;

#pragma endregion

#pragma region /** Freezing */

	/** checks if player is freezing and if he is take damage */
	UFUNCTION(BlueprintCallable)
	void TakeDamageFromFreezing(float DamageAmount);

	/** damage to deal every 0.1 second from freezing */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Damage")
	float DamageFromFreezing = 0.0025f;

#pragma endregion

#pragma region /** Fall Damage */

	/*
	 * Damage dealt by falling from high place.
	 * It will be multiplied by meters that player has fallen from
	*/
	UPROPERTY(BlueprintReadWrite, Category = "FallDamage")
	double DamageFromFalling;

	/** take damage if player falls from a high place */
	UFUNCTION(BlueprintCallable)
	void TakeFallDamage(float DamageAmount);

#pragma endregion

};
