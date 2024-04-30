// Individual developer Adrian Filipek.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "OnlyExample/public/ItemData.h"
#include "CookFoodOrPrepareDrinkWidget.generated.h"

/**
 * 
 */
UCLASS()
class ONLYEXAMPLE_API UCookFoodOrPrepareDrinkWidget : public UCommonButtonBase
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

	virtual void NativeOnDoubleClicked() override;

protected:

	UPROPERTY()
	class AExampleChar* MyExampleChar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* FoodName;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* FoodImage;
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = " Item ")
	FItemData ItemData_Temp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = " Item ")
	int IndexTemp;

	virtual void NativeOnClicked() override;

};
