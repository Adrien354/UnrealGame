// Individual developer Adrian Filipek.


#include "ITMAccelerator.h"

AITMAccelerator::AITMAccelerator()
{
	ItemData.Name = "Accelerant";
	ItemData.Description = "It is a gas that accelerates starting a fire.";
	ItemData.Condition = 100;
	ItemData.Weight = 0.2f;
	ItemData.HeatDataStruct.Category = EHeatCategory::Accelerant;
	ItemData.HeatDataStruct.BonusStartingFire = 0.5f;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BaseMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Pipe.Shape_Pipe'"));
	if(BaseMesh.Succeeded())
	{
		Model->SetStaticMesh(BaseMesh.Object);
	}
}