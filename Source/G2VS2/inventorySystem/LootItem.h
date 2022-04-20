// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "GameFramework/Actor.h"
#include "LootItem.generated.h"

UCLASS()
class G2VS2_API ALootItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALootItem();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		UStaticMesh* ItemAvatar;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
		UItem* Item;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
