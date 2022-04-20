// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DisplayItem.generated.h"

UCLASS()
class G2VS2_API ADisplayItem : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ADisplayItem();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Item")
	UStaticMesh* ItemAvatar;

protected:
	//// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	


};
