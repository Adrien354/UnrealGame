// Fill out your copyright notice in the Description page of Project Settings.


#include "Wind_CPP.h"
#include "OnlyExample/ExampleChar.h"

// Sets default values
AWind_CPP::AWind_CPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 50.f;

}

// Called when the game starts or when spawned
void AWind_CPP::BeginPlay()
{
	Super::BeginPlay();
	
	//Cast to my character
	MyExampleCharRef = Cast<AExampleChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	//Get this object reference to ExampleCharacter
	MyExampleCharRef->WindObjectRef = this;

	//Get arrow component
	WindDirectionArrow = FindComponentByClass<UArrowComponent>();

	//Set ZRotation when game starts
	ZRotation = FMath::RandRange(0.f, 360.f);

	//Set rotation of WindDirection component
	if (WindDirectionArrow != nullptr) {
		WindDirectionArrow->SetWorldRotation(FRotator(0.f, ZRotation, 0.f));
	}
	
}

// Called every frame
void AWind_CPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetWindDirection();
}

void AWind_CPP::SetWindDirection() {
	if (ZRotation >= 360.f) {
		ZRotation = 0.1f;
	}
	else if(ZRotation <= 0){
		ZRotation = 359.f;
	}
	else {
		ZRotation = FMath::RandRange((ZRotation - 10.f), (ZRotation + 10.f));
	}

	WindDirectionArrow->SetWorldRotation(FRotator(0.f, ZRotation, 0.f));
}

