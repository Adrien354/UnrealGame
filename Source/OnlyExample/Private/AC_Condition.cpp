// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_Condition.h"

#include "Logging/StructuredLog.h"

// Sets default values for this component's properties
UAC_Condition::UAC_Condition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 5.f;
}


// Called when the game starts
void UAC_Condition::BeginPlay()
{
	Super::BeginPlay();

	MyExampleCharRef = Cast<AExampleChar>(GetOwner());
	
}


// Called every frame
void UAC_Condition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateConditionOfItems();
	MyExampleCharRef->SetFeelsLikeVariable();
}

void UAC_Condition::UpdateConditionOfItems()
{
	if (MyExampleCharRef->InventoryList.IsEmpty())
		return;

	int length = MyExampleCharRef->InventoryList.Num();

	for (int i = 0; i < length; i++) {
		if (MyExampleCharRef->InventoryList[i].Category == EItemCategory::Weapons && MyExampleCharRef->InventoryList[i].Category == EItemCategory::Heat)
			return;

		if ((MyExampleCharRef->InventoryList[i].Category == EItemCategory::Clothing && MyExampleCharRef->InventoryList[i].ClothingDataStruct.bIsWearing) || MyExampleCharRef->InventoryList[i].Category == EItemCategory::Food) {
			MyExampleCharRef->InventoryList[i].Condition = 
				MyExampleCharRef->InventoryList[i].Condition - ((MyExampleCharRef->InventoryList[i].Decay / 24.f / 60.f) * ConditionLooseMultiplier);
		}
	}
}

