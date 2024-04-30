// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_PlayerHealth.h"

// Sets default values for this component's properties
UAC_PlayerHealth::UAC_PlayerHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 0.5f;
}


// Called when the game starts
void UAC_PlayerHealth::BeginPlay()
{
	Super::BeginPlay();

	//Get a owner of this actor component
	ExampleCharRef = Cast<AExampleChar>(GetOwner());
	
}


// Called every frame
void UAC_PlayerHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (FMath::IsNearlyZero(ExampleCharRef->Calories)) {
	TakeDamageFromStarving(DamageFromStarving);
	}

	//Take damage if player's warmth is equal 0
	if (FMath::IsNearlyZero(ExampleCharRef->Warmth)) {
		TakeDamageFromFreezing(DamageFromFreezing);
	}
}

void UAC_PlayerHealth::TakeDamageFromStarving(float DamageAmount)
{

	//take 1.5 damage per hour if player is starving less than hour
	float Damage = DamageAmount * DamageMultiplier;
	ExampleCharRef->TakeDamage(Damage);
	DamageDealt += Damage;

	//Take more damage if player is starving more than an hour
	if (DamageDealt > 1.5f) {
		//After hour take two and a half more damage than earlier so it is 3.75 damage per hour
		ExampleCharRef->TakeDamage(Damage * 2.5f);
	}
	//Take even more damage if the player is starving more than 3 hours
	else if (DamageDealt > 9.f) {
		//After 3 hours take 10 times more damage than in first hour. So the damage per hour will be 
		ExampleCharRef->TakeDamage(Damage * 10.f);
	}
}

void UAC_PlayerHealth::TakeDamageFromFreezing(float DamageAmount)
{

	//Damage multiplied by multiplier
	//this is made for sleeping system if player sleeps tick interval is set to 50 times more than it was
	//That means the tick function will be called less than before
	//So my solution was to multiply given value by some multiplier and it works just fine
	float Damage = DamageAmount * DamageMultiplier;

	//Deacrese condition by given value
	ExampleCharRef->TakeDamage(Damage);
}

/** I HAVE TO IMPLEMENT THIS SECTION IF ONLY I'M DONE WITH THE MOST IMPORTANT THINGS */
void UAC_PlayerHealth::TakeFallDamage(float DamageAmount)
{
}

