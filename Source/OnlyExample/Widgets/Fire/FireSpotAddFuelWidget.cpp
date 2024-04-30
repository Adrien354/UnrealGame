// Individual developer Adrian Filipek.


#include "FireSpotAddFuelWidget.h"
#include "Components/ScrollBox.h"
#include "AddFuelButton.h"
#include "OnlyExample/ExampleChar.h"
#include "Kismet/GameplayStatics.h"

void UFireSpotAddFuelWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	MyExampleChar = Cast<AExampleChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	CreateAddFuelButtons();
}

void UFireSpotAddFuelWidget::CreateAddFuelButtons()
{
	if (MyExampleChar == nullptr || MyExampleChar->InventoryList.IsEmpty())
		return;

	int length = MyExampleChar->InventoryList.Num();
	TArray<FItemData> tempInventoryList = MyExampleChar->InventoryList;

	for (int i = 0; i < length; i++) {
		if (tempInventoryList[i].Category == EItemCategory::Heat && tempInventoryList[i].HeatDataStruct.Category == EHeatCategory::Fuel) {

			AddFuelButtonWidget = nullptr;
			this->FuelScrollBox->AddChild(CreateFuelButtonsWidgets(tempInventoryList[i], i));
		}
	}
	
}

UAddFuelButton* UFireSpotAddFuelWidget::CreateFuelButtonsWidgets(FItemData ItemData, int index)
{
	AddFuelButtonWidget = CreateWidget<UAddFuelButton>(MyExampleChar->PC, AddFuelButtonClass);
	AddFuelButtonWidget->ItemData_Temp = ItemData;
	AddFuelButtonWidget->IndexTemp = index;
	AddFuelButtonWidget->AddToPlayerScreen();

	return AddFuelButtonWidget;
}

