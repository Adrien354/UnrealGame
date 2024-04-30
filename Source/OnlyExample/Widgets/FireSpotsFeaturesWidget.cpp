// Individual developer Adrian Filipek.


#include "FireSpotsFeaturesWidget.h"
#include "OnlyExample/ExampleChar.h"
#include "Blueprint/UserWidget.h"
#include "OnlyExample/Interactive/FireSpots/F_Parent.h"


void UFireSpotsFeaturesWidget::NativeConstruct()
{
    Super::NativeConstruct();
	
	BTNCook->OnClicked.AddDynamic(this, &UFireSpotsFeaturesWidget::OnClickedCook);
	BTNAddfuel->OnClicked.AddDynamic(this, &UFireSpotsFeaturesWidget::OnClickedAddFuel);
	BTNCancel->OnClicked.AddDynamic(this, &UFireSpotsFeaturesWidget::OnClickedCancel);

	MyExampleChar = Cast<AExampleChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	BTNCook->SetIsEnabled(!MyExampleChar->FireSpot_BP->FireSpotData.bIsCooking);
}

void UFireSpotsFeaturesWidget::OnClickedCook()
{
	//Checks if the character is valid
	if (MyExampleChar == nullptr)
		return;

	MyExampleChar->CreateFireSpotCookWidget();

	this->RemoveFromParent();
}

void UFireSpotsFeaturesWidget::OnClickedAddFuel()
{
	//Checks if the character is valid
	if (MyExampleChar == nullptr)
		return;
	
	MyExampleChar->CreateFireSpotAddFuelWidget();

	this->RemoveFromParent();
}

void UFireSpotsFeaturesWidget::OnClickedCancel()
{

	//unset variables
	MyExampleChar->bInventoryActive = false;
	MyExampleChar->bIsSearching = false;
	MyExampleChar->bIsStartFireActive = false;

	MyExampleChar->PC->bShowMouseCursor = false;
	MyExampleChar->PC->SetInputMode(FInputModeGameOnly());
	
	MyExampleChar->W_FireSpotFeatures->RemoveFromParent();
	//Remove from player screen
	MyExampleChar->W_FireSpotFeatures = nullptr;
	MyExampleChar->ActorTraced = nullptr;
	
}

