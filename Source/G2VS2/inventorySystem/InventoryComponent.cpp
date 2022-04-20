// Fill out your copyright notice in the Description page of Project Settings.


#include  "Item.h"
#include "Containers/Map.h"
#include "inventorySystem/InventoryComponent.h"


UInventoryComponent::UInventoryComponent()
{
	Capacity = 20;

}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	//for (auto& Item : DefaultItemsMap)
	//{
	//	/*AddItem1(Item.Key, Item.Value);*/
	//}

}

//
//bool UInventoryComponent::AddItem1(class TSubclassOf<class UItem> Item, int32 Amount)
//{
//	if (ItemsMap.Num() >= Capacity || !Item)
//	{
//		return false;
//	}
//
//	/*Item->OwningInventory = this;
//	Item->World = GetWorld();*/
//	ItemsMap.Add(Item);
//
//	
//
//	return true;
//}
//
//bool UInventoryComponent::RemoveItem1(class TSubclassOf<class UItem> Item, int32 Amount)
//{
//	if (Item)
//	{
//	/*	Item->OwningInventory = nullptr;
//		Item->World = nullptr;*/
//		ItemsMap.Remove(Item);
//		
//		return true;
//	}
//	return false;
//}
