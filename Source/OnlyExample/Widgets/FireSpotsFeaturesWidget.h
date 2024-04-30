// Individual developer Adrian Filipek.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Fire/FireSpotCookWidget.h"
#include "Blueprint/UserWidget.h"
#include "FireSpotsFeaturesWidget.generated.h"

/**
 * 
 */
UCLASS()
class ONLYEXAMPLE_API UFireSpotsFeaturesWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void NativeConstruct() override;

public:

	/**Reference to ExampleChar*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Character")
	class AExampleChar* MyExampleChar;

	/** Button to return to game */
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* BTNCancel;

	/** Called when button cancel is clicked */
	UFUNCTION(BlueprintCallable)
	void OnClickedCancel();
	
#pragma region /** Cook */
	/** Button to cook */
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* BTNCook;

	/** Called when button cook is clicked */
	UFUNCTION(BlueprintCallable)
	void OnClickedCook();

#pragma endregion

#pragma region /** Add Fuel */
public:
	/** Button to add fuel */
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* BTNAddfuel;

	UFUNCTION(BlueprintCallable)
	void OnClickedAddFuel();
#pragma endregion

};
