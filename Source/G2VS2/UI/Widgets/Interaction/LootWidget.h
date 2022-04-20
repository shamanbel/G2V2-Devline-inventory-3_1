// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LootWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class G2VS2_API ULootWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
	void OnCloseButtonPressed();
	
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* CloseButton;
	
};
