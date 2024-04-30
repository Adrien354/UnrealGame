// Individual developer Adrian Filipek.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Variables/FireSpotData.h"
#include "OnlyExample/Public/ItemFoodData.h"
#include "F_Parent.generated.h"

/*
 *F_Parent is a parent class for all fire spots
*/
UCLASS()
class ONLYEXAMPLE_API AF_Parent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AF_Parent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float TimeToCook;

	/** Struct to get all information of this fire spot */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Default")
	FS_CanStartFires_data FireSpotData;

	/** */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Fire")
	FItemFoodData FoodData;

	UFUNCTION(BlueprintCallable, Category = "FireSystem")
	void FireSystem();

	//Variable to keep spawned actor
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Fire")
	TObjectPtr<AActor> SpawnedActor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Fire")
	FTransform SpawnTransform;

	TObjectPtr<class AExampleChar> MyExampleChar;

	/**  */
	UFUNCTION(BlueprintCallable, Category = "CookSystem")
	void CookSystem(AActor* BaseItem, FItemFoodData FoodDataStruct);

	UFUNCTION()
	void CookFood();
};
