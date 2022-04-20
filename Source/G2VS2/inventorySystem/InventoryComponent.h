// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LootItem.h"
//#include "Player/PlayerCharacter.h"
#include "InventoryComponent.generated.h"


UCLASS(BlueprintType, Blueprintable, DefaultToInstanced, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class G2VS2_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	virtual void BeginPlay() override;

	/*UFUNCTION(BlueprintCallable)
	bool AddItem1(class TSubclassOf<class UItem> Item, int32 Amount);

	UFUNCTION(BlueprintCallable)
	bool RemoveItem1(class TSubclassOf<class UItem> Item, int32 Amount);*/



	//, Instancedgh

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
	TMap<class UItem*, int32> DefaultItemsMap;
	//TMap<class TSubclassOf<class UItem>, int32> DefaultItemsMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
	TMap<class TSubclassOf<class UItem>, int32> ItemsMap;


	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	int Capacity;



protected:
	

		
};
