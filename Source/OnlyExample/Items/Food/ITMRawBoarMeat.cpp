// Individual developer Adrian Filipek.


#include "ITMRawBoarMeat.h"
#include "Meat/ITMCookedBoarMeat.h"

AITMRawBoarMeat::AITMRawBoarMeat()
{
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BaseMeshAsset(TEXT("StaticMesh'/Game/Models/Items/S_Smoked_Meat_weuhdcyaa_lod3_Var1.S_Smoked_Meat_weuhdcyaa_lod3_Var1'"));
	if(BaseMeshAsset.Succeeded())
		Model->SetStaticMesh(BaseMeshAsset.Object);

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> BaseMaterialAsset(TEXT("/Game/Materials/Food/Raw_Meat_Texture.Raw_Meat_Texture"));

	Model->SetMaterial(0, BaseMaterialAsset.Object);

	/*
	 * Set up the Item data to this specific item.
	 */
	ItemData.Category = EItemCategory::Food;
	ItemData.Name = "Raw Boar Meat";
	ItemData.Description = "Raw meat from a boar. It's not safe to eat it raw.";
	ItemData.Weight = 1.f;
	ItemData.Condition = 100.0f;
	ItemData.Decay = 0.1f;
	ItemData.FoodDataStruct.Calories = 550.f;
	ItemData.FoodDataStruct.bCanBeCooked = true;
	ItemData.FoodDataStruct.bIsEatable = true;
	ItemData.FoodDataStruct.CookedItem = AITMCookedBoarMeat::StaticClass();
	ItemData.FoodDataStruct.TimeToCook = 10.f;
}