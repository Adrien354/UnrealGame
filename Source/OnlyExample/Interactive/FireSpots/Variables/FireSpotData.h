// Individual developer Adrian Filipek.

#pragma once

#include "CoreMinimal.h"
#include "FireSpotData.generated.h"
/**  */
USTRUCT(BlueprintType)
struct FS_CanStartFires_data
{
	GENERATED_BODY()
public:
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Name"))
	FString Name;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="bIsBurning", MakeStructureDefaultValue="False"))
	bool bIsBurning;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="EstimatedMinutesBurning", MakeStructureDefaultValue="0"))
	int32 EstimatedMinutesBurning;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Temperature", MakeStructureDefaultValue="0.000000"))
	double Temperature;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "bIsCooking", MakeStructureDefaultValue = "False"))
	bool bIsCooking;

	/** How many spots are available to cook */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "SpotsForCooking", MakeStructureDefaultValue = "1"))
	int32 SpotsForCooking;

	

};
