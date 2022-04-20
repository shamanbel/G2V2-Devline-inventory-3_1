// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/NoExportTypes.h"
#include "EnvironmentTypes.generated.h"

USTRUCT(BlueprintType)
struct FDayTimeInterval
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Meta = (ClampMin="1", ClampMax="24"))
	int32 StartTime = 1;

	UPROPERTY(EditAnywhere, Meta = (ClampMin="1", ClampMax="24"))
	int32 EndTime = 24;
};

/**
 * Empty class required by some types and reflection system 
 */
UCLASS()
class G2VS2_API UEnvironmentTypes : public UObject
{
	GENERATED_BODY()
	
};
