// Individual developer Adrian Filipek.

#pragma once

#include "CoreMinimal.h"
#include "OnlyExample/Public/ItemData.h"
#include "CommonButtonBase.h"
#include "AddFuelButton.generated.h"

/**
 * 
 */
UCLASS()
class ONLYEXAMPLE_API UAddFuelButton : public UCommonButtonBase
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

	virtual void NativeOnDoubleClicked() override;

protected:

	UPROPERTY()
	class AExampleChar* MyExampleChar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* FuelName;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* FuelImage;
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = " Item ")
	FItemData ItemData_Temp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = " Item ")
	int IndexTemp;

	virtual void NativeOnClicked() override;

	FTimerHandle TimerHandle;

};
