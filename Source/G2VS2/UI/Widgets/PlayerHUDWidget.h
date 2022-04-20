// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "Core/GameTypes.h"
#include "PlayerHUDWidget.generated.h"

class ULootWidget;

/**
 * 
 */
UCLASS(abstract)
class G2VS2_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
	void OnInteractActorChanged(AActor* NewInteract, const EInteractionPhase InteractionPhase);
	
public:
	void ShowLootWidget(const bool bShow);
	
protected:
	UPROPERTY(meta = (BindWidget))
	ULootWidget* LootWidget;
};
