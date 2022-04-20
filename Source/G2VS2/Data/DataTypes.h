// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "DataTypes.generated.h"

class APickupActor;

USTRUCT(BlueprintType)
struct FPickupData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Assets")
	FGuid UniqueID;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Assets")
	TSoftObjectPtr<UStaticMesh> WorldMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Assets")
	TSoftObjectPtr<USkeletalMesh> InventoryMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Assets")
	TSubclassOf<APickupActor> ActorClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Assets")
	uint8 bCustomGeometryClass : 1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FText Description;

	bool IsValid() const;

	FPickupData();
};

/**
 * Contains various methods to manipulate with data 
 */
UCLASS()
class G2VS2_API UDataTypes : public UObject
{
	GENERATED_BODY()
	
};
