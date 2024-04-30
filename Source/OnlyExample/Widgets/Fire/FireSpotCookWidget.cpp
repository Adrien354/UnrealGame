// Individual developer Adrian Filipek.


#include "FireSpotCookWidget.h"
#include "Components/ScrollBox.h"
#include "OnlyExample/Widgets/Fire/CookFoodOrPrepareDrinkWidget.h"
#include "OnlyExample/ExampleChar.h"
#include <Kismet/GameplayStatics.h>

void UFireSpotCookWidget::NativeConstruct()
{
    Super::NativeConstruct();

   MyExampleChar = Cast<AExampleChar>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

   CreateCookFoodButtons();
}

void UFireSpotCookWidget::CreateCookFoodButtons() 
{
    if (MyExampleChar == nullptr || MyExampleChar->InventoryList.IsEmpty())
        return;
    
    int length = MyExampleChar->InventoryList.Num();
    TArray<FItemData> tempInventoryList = MyExampleChar->InventoryList;

    for (int i = 0; i < length; i++) {
        if (tempInventoryList[i].Category == EItemCategory::Food && 
            tempInventoryList[i].FoodDataStruct.bCanBeCooked) {

            CookFoodOrPrepareDrinkWidget = nullptr;
            this->FoodScrollBox->AddChild(CreateFoodToCookButton(tempInventoryList[i], i));
        }
    }
}

UCookFoodOrPrepareDrinkWidget* UFireSpotCookWidget::CreateFoodToCookButton(FItemData ItemData, int index) 
{
    CookFoodOrPrepareDrinkWidget = CreateWidget<UCookFoodOrPrepareDrinkWidget>(MyExampleChar->PC, CookFoodOrPrepareDrinkWidgetClass);
    CookFoodOrPrepareDrinkWidget->ItemData_Temp = ItemData;
    CookFoodOrPrepareDrinkWidget->IndexTemp = index;
    CookFoodOrPrepareDrinkWidget->AddToViewport();

    return CookFoodOrPrepareDrinkWidget;
}
