// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagAssetInterface.h"
#include "GameFramework/Actor.h"
#include "Interfaces/InteractionInterface.h"
#include "InteractableActor.generated.h"

UCLASS()
class G2VS2_API AInteractableActor : public AActor, public IGameplayTagAssetInterface, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	AInteractableActor();

	virtual void PostInitializeComponents() override;
	
	//~ Begin InteractionInterface Interface
	virtual void GetInteractionLabel_Implementation(FInteractionLabel& OutLabel) override;
	virtual bool CanInteract_Implementation() const override;
	virtual void GetInteractionType_Implementation(FGameplayTag& OutType) override;
	virtual void GetInteractionLocation_Implementation(FInteractionLocation& OutLocation) override;
	//~ End InteractionInterface Interface

	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameplayTags")
	FGameplayTagContainer GameplayTags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	FInteractionLabel InteractionLabel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	FGameplayTag InteractionType;
};
