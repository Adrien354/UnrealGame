// Individual developer Adrian Filipek.


#include "ITM_Parent.h"

// Sets default values
AITM_Parent::AITM_Parent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	Model = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Model"));
	Model->SetupAttachment(RootComponent);
}

void AITM_Parent::BeginPlay()
{
	Super::BeginPlay();
}

void AITM_Parent::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	ItemData.ItemClass = this;
}


