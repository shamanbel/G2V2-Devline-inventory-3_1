// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameTypes.h"
#include "GameplayTagContainer.h"
#include "Engine/DeveloperSettings.h"
#include "InteractionSettings.generated.h"

/**
 * 
 */
UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "Interactions"))
class G2VS2_API UInteractionSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	UInteractionSettings();

	virtual void PostInitProperties() override;
	
public:
	UPROPERTY(Config, EditDefaultsOnly, Category = Player)
	FInteractionLabel DefaultInteractionLabel;
	
	//Distance with player will be notices about interactable actors
	UPROPERTY(Config, EditDefaultsOnly, Category = Player)
	float InteractionDistance = 500.f;

	//Period to check about new interactions around player
	UPROPERTY(Config, EditDefaultsOnly, Category = Player)
	float CheckFocusTime = 0.3f;

	UPROPERTY(Config, EditDefaultsOnly, Category = General)
	FGameplayTag DefaultPickupTag;

	UPROPERTY(Config, EditDefaultsOnly, Category = General)
	FGameplayTag DefaultLootTag;
};
