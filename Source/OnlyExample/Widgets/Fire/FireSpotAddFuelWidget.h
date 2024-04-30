// Individual developer Adrian Filipek.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "FireSpotAddFuelWidget.generated.h"

/**
 * 
 */
UCLASS()
class ONLYEXAMPLE_API UFireSpotAddFuelWidget : public UCommonUserWidget
{
	GENERATED_BODY()

	// Called when the game starts or when spawned
	virtual void NativeConstruct() override;
	
public:

	
	/** Reference to ScrollBox */
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UScrollBox* FuelScrollBox;

	//Create cook food buttons
	UFUNCTION(BlueprintCallable)
	void CreateAddFuelButtons();

	UFUNCTION(BlueprintCallable)
	class UAddFuelButton* CreateFuelButtonsWidgets(FItemData ItemData, int index);

protected:
	//My character reference
	TObjectPtr<class AExampleChar> MyExampleChar;

public:
	/** Get subclass of widget to create it */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AddFuel")
	TSubclassOf<class UAddFuelButton> AddFuelButtonClass;

	/**Reference to AddFuelButton*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "AddFuel")
	class UAddFuelButton* AddFuelButtonWidget;
};
