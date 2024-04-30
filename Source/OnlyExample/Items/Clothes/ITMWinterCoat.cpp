// Individual developer Adrian Filipek.


#include "ITMWinterCoat.h"

#include "IDetailTreeNode.h"

AITMWinterCoat::AITMWinterCoat()
{
	ItemData.Name = "Winter Coat";
	ItemData.Condition = 100;
	ItemData.Decay = 0.2f;
	ItemData.Weight = 8.0f;
	ItemData.Description = "A warm winter coat. Best solution for windy and cold days.";
	ItemData.ClothingDataStruct.bIsWearing = false;
	ItemData.ClothingDataStruct.CategoryOfClothes = EItemClothesCategory::Jacket;
	ItemData.ClothingDataStruct.WarmthBonus = 5.0f;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BaseMeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Torus.Shape_Torus'"));
	if(BaseMeshAsset.Succeeded())
		Model->SetStaticMesh(BaseMeshAsset.Object);
}
