// Individual developer Adrian Filipek.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "FireSpotCookWidget.generated.h"

/**
 * 
 */
UCLASS()
class ONLYEXAMPLE_API UFireSpotCookWidget : public UCommonUserWidget
{
	GENERATED_BODY()
	
	// Called when the game starts or when spawned
	virtual void NativeConstruct() override;

	
	//My character reference
	TObjectPtr<class AExampleChar> MyExampleChar;
	
public:
	//Create cook food buttons
	UFUNCTION(BlueprintCallable)
	void CreateCookFoodButtons();

	UFUNCTION(BlueprintCallable)
	class UCookFoodOrPrepareDrinkWidget* CreateFoodToCookButton(FItemData ItemData, int index);
	
	/** Reference to ScrollBox */
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UScrollBox* FoodScrollBox;

	/** Get subclass of widget to create it */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FireSpotCookWidget")
	TSubclassOf<class UCookFoodOrPrepareDrinkWidget> CookFoodOrPrepareDrinkWidgetClass;

	/**Reference to CookFoodOrPrepareDrink*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "FireSpotCookWidget")
	class UCookFoodOrPrepareDrinkWidget* CookFoodOrPrepareDrinkWidget;
};
