// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentTypes.h"
#include "GameplayTagContainer.h"
#include "Engine/DeveloperSettings.h"
#include "DateTimeSystemSettings.generated.h"

/**
 * 
 */
UCLASS(config = Game, defaultconfig, meta = (DisplayName = "World Date and Time"))
class G2VS2_API UDateTimeSystemSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UDateTimeSystemSettings();
	
	UPROPERTY(config, EditDefaultsOnly)
	FTimespan InitialDateTime;

	UPROPERTY(config, EditDefaultsOnly)
	float TimeRate;
	
	UPROPERTY(config, EditDefaultsOnly)
	TMap<FGameplayTag, FDayTimeInterval> TimesOfDay;

	UPROPERTY(config, EditDefaultsOnly, Category=Development)
	TSubclassOf<UUserWidget> DateTimeWidgetClass;
};
