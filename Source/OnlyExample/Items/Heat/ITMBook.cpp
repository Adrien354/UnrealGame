// Individual developer Adrian Filipek.


#include "ITMBook.h"

AITMBook::AITMBook()
{
	ItemData.Name = "Book";
	ItemData.Description = "A book. Source of fire";
	ItemData.Category = EItemCategory::Heat;
	ItemData.Weight = 0.5f;
	ItemData.Condition = 100.f;
	ItemData.HeatDataStruct.BonusStartingFire = 0.15f;
	ItemData.HeatDataStruct.Category = EHeatCategory::Fuel;
	ItemData.HeatDataStruct.MinutesBurning = 26;
	ItemData.HeatDataStruct.GeneratedHeat = 6.f;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BaseMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Trim.Shape_Trim'"));
	if(BaseMesh.Succeeded())
	{
		Model->SetStaticMesh(BaseMesh.Object);
	}

}