// Individual developer Adrian Filipek.


#include "ITMMatches.h"

AITMMatches::AITMMatches()
{
	ItemData.Name = "Matches";
	ItemData.Description = "A box of matches.";
	ItemData.Condition = 100.f;
	ItemData.Weight = 0.1f;
	ItemData.HeatDataStruct.Category = EHeatCategory::FireStarter;
	ItemData.HeatDataStruct.BonusStartingFire = 0.10f;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if(MeshAsset.Succeeded())
		Model->SetStaticMesh(MeshAsset.Object);

}