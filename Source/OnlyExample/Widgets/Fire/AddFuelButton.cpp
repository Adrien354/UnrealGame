// Individual developer Adrian Filipek.


#include "AddFuelButton.h"
#include "Components/ScrollBox.h"
#include "FireSpotAddFuelWidget.h"
#include "Components/Image.h"
#include "OnlyExample/ExampleChar.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Logging/StructuredLog.h"
#include "OnlyExample/Interactive/FireSpots/F_Parent.h"

void UAddFuelButton::NativeConstruct()
{
	Super::NativeConstruct();

	MyExampleChar = Cast<AExampleChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	FuelName->SetText(FText::FromString(ItemData_Temp.Name));
	FuelImage->SetBrushFromTexture(ItemData_Temp.Image);
}

void UAddFuelButton::NativeOnClicked()
{
	Super::NativeOnClicked();

	if (MyExampleChar == nullptr)
		return;

	UE_LOGFMT(LogTemp, Log, "Clicked {0}", ItemData_Temp.Name);
}

void UAddFuelButton::NativeOnDoubleClicked()
{
	Super::NativeOnDoubleClicked();

	if (MyExampleChar == nullptr)
		return;

	float temperature = MyExampleChar->FireSpot_BP->FireSpotData.Temperature;
	MyExampleChar->FireSpot_BP->FireSpotData.EstimatedMinutesBurning += ItemData_Temp.HeatDataStruct.MinutesBurning;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([=, this]()
	{
		MyExampleChar->FireSpot_BP->FireSpotData.Temperature += 1;
		if(MyExampleChar->FireSpot_BP->FireSpotData.Temperature - ItemData_Temp.HeatDataStruct.GeneratedHeat == temperature)
		{
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		}
	}), 0.1f, true);
	MyExampleChar->InventoryList.RemoveAt(IndexTemp);

	MyExampleChar->FireSpotAddFuelWidget->FuelScrollBox->ClearChildren();
	MyExampleChar->FireSpotAddFuelWidget->CreateAddFuelButtons();
}
