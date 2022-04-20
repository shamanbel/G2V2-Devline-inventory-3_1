// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/GameTypes.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "InteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable, MinimalAPI)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class G2VS2_API IInteractionInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category ="Interaction|General")
	void BeginInteract(UObject* InteractionInstigator, const FHitResult& InteractionHit);

	UFUNCTION(BlueprintNativeEvent, Category ="Interaction|General")
	void EndInteract(UObject* InteractionInstigator);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category ="Interaction|General")
	bool CanInteract() const;

	//Object reaction when focus gain on it
	UFUNCTION(BlueprintNativeEvent, Category ="Interaction|General")
	void GainFocus(UObject* InteractionInstigator);

	//Object reaction when focus lost on it
	UFUNCTION(BlueprintNativeEvent, Category ="Interaction|General")
	void LostFocus(UObject* InteractionInstigator);

	//Where AI or player should be placed to interact
	UFUNCTION(BlueprintNativeEvent, Category ="Interaction|General")
	void GetInteractionLocation(FInteractionLocation& OutLocation);

	UFUNCTION(BlueprintNativeEvent, Category ="Interaction|General")
	void GetInteractionType(FGameplayTag& OutType);
	
	//Used to provide UI data for interaction
	UFUNCTION(BlueprintNativeEvent, Category ="Interaction|UI")
	void GetInteractionLabel(FInteractionLabel& OutLabel);

	
};
