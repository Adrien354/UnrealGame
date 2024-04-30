// Individual developer Adrian Filipek.


#include "ITMStackOfPapers.h"

AITMStackOfPapers::AITMStackOfPapers()
{
	ItemData.Name = "Stack of Papers";
	ItemData.Description = "A stack of papers. Not bad for setting a fire.";
	ItemData.Weight = 0.1f;
	ItemData.Condition = 100;
	ItemData.HeatDataStruct.Category = EHeatCategory::Tinder;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BaseMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_WideCapsule.Shape_WideCapsule'"));

	if (BaseMesh.Succeeded())
	{
		Model->SetStaticMesh(BaseMesh.Object);
	}
}