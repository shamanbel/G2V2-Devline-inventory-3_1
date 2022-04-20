// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionInfoWidget.generated.h"

class UTextBlock;
class UImage;

/**
 * 
 */
UCLASS(abstract)
class G2VS2_API UInteractionInfoWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeDestruct() override;
	
	UFUNCTION()
	void OnFocusActorChanged(AActor* NewFocus);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* InteractionText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* InputText;

	UPROPERTY(meta = (BindWidget))
	UImage* InputIcon;
	
private:
	TWeakObjectPtr<AActor> ManagedActor;
};
