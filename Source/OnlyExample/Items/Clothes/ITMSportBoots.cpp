// Individual developer Adrian Filipek.


#include "ITMSportBoots.h"

AITMSportBoots::AITMSportBoots()
{
	ItemData.Name = "Sport Boots";
	ItemData.Condition = 100;
	ItemData.Decay = 0.2f;
	ItemData.Weight = 1.0f;
	ItemData.Description = "A pair of sport boots. Perfect for running and other activities.";
	ItemData.ClothingDataStruct.bIsWearing = false;
	ItemData.ClothingDataStruct.CategoryOfClothes = EItemClothesCategory::Shoe;
	ItemData.ClothingDataStruct.WarmthBonus = 1.5f;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BaseMeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if(BaseMeshAsset.Succeeded())
		Model->SetStaticMesh(BaseMeshAsset.Object);

	Model->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
}
