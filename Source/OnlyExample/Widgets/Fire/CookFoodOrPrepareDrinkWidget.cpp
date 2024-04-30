// Individual developer Adrian Filipek.


#include "CookFoodOrPrepareDrinkWidget.h"
#include "Kismet/GameplayStatics.h"
#include "OnlyExample/ExampleChar.h"
#include "OnlyExample/Interactive/FireSpots/F_Parent.h"
#include "OnlyExample/Widgets/Fire/FireSpotCookWidget.h"
#include "Components/Image.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Logging/StructuredLog.h"

void UCookFoodOrPrepareDrinkWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MyExampleChar = Cast<AExampleChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	FoodName->SetText(FText::FromString(ItemData_Temp.Name));
	FoodImage->SetBrushFromTexture(ItemData_Temp.Image);
}

void UCookFoodOrPrepareDrinkWidget::NativeOnClicked()
{
	Super::NativeOnClicked();

	if (MyExampleChar == nullptr)
		return;

	UE_LOGFMT(LogTemp, Log, "Clicked {0}", ItemData_Temp.Name);
}

void UCookFoodOrPrepareDrinkWidget::NativeOnDoubleClicked()
{
	Super::NativeOnDoubleClicked();

	if (MyExampleChar == nullptr || MyExampleChar->FireSpot_BP->FireSpotData.bIsCooking == true)
		return;
	
	MyExampleChar->FireSpot_BP->CookSystem(ItemData_Temp.ItemClass, ItemData_Temp.FoodDataStruct);
	MyExampleChar->InventoryList.RemoveAt(IndexTemp);
	MyExampleChar->RemoveFireSpotCookWidget();
	

}