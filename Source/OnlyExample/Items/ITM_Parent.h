// Individual developer Adrian Filipek.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OnlyExample/public/ItemData.h"
#include "ITM_Parent.generated.h"


/**
 *  Parent class for all items in the game
 */
UCLASS()
class ONLYEXAMPLE_API AITM_Parent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AITM_Parent();

    virtual void BeginPlay() override;

	/** */
	virtual void OnConstruction(const FTransform& Transform) override;
	 

    /** Please add a variable description */
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Default")
    FItemData ItemData;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Default")
	TObjectPtr<UStaticMeshComponent> Model;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Default")
	TObjectPtr<USceneComponent> DefaultSceneRoot;

};
