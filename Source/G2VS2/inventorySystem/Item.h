// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "DisplayItem.h"
#include "Item.generated.h"

USTRUCT(BlueprintType)
struct FInventory : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FName ID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FString Type;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	FText ShortDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item", meta = (MultiLine = true))
	FText LongDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	class UTexture2d* Icon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	TSubclassOf<class UItem> Item;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	bool CanStack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	UStaticMesh* StaticMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	TSubclassOf<class ADisplayItem> DisplayItem;




};


UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)

class G2VS2_API UItem : public UObject
{
	GENERATED_BODY()



public:

	UItem();

	virtual class UWorld* GetWorld() const { return World; };

	UPROPERTY(Transient)
		class UWorld* World;

	UPROPERTY(VisibleAnywhere, Category = "Item")
		FInventory ItemInventory;


	UPROPERTY()
	class UInventoryComponent* OwningInventory;

	virtual void Use(class APlayerCharacter* Character);

	UFUNCTION(BlueprintImplementableEvent)
	void On_Use(class APlayerCharacter* Character);

	/*	virtual void Equipment(class APlayerCharacter* Character) PURE_VIRTUAL(UItem,);
		virtual void DeEquipment(class APlayerCharacter* Character) PURE_VIRTUAL(UItem, );*/

};
