// Individual developer Adrian Filipek.


#include "ITMCookedBoarMeat.h"

AITMCookedBoarMeat::AITMCookedBoarMeat()
{
	ItemData.Name = "Cooked Boar Meat";
	ItemData.Condition = 100.0f;
	ItemData.Decay = 0.3f;
	ItemData.Description = "Cooked meat from a boar. It's safe to eat.";
	ItemData.Weight = 1.f;
	ItemData.FoodDataStruct.Calories = 550.f;
	ItemData.FoodDataStruct.bCanBeCooked = false;
	ItemData.FoodDataStruct.bIsEatable = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BaseMeshAsset(TEXT("StaticMesh'/Game/Models/Items/S_Smoked_Meat_weuhdcyaa_lod3_Var1.S_Smoked_Meat_weuhdcyaa_lod3_Var1'"));
	if(BaseMeshAsset.Succeeded())
		Model->SetStaticMesh(BaseMeshAsset.Object);
}
