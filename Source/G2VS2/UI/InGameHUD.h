// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/HUD.h"
#include "InGameHUD.generated.h"

class UPlayerHUDWidget;
class UInteractionInfoWidget;
/**
 * 
 */
UCLASS()
class G2VS2_API AInGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	AInGameHUD();
	virtual void PostInitializeComponents() override;
	
protected:
	virtual void BeginPlay() override;
	
public:
	template <typename WidgetT = UUserWidget>
	WidgetT* ShowWidget(TSubclassOf<UUserWidget> UserWidgetClass = WidgetT::StaticClass())
	{
		
		WidgetT* InWidget = CreateWidget<WidgetT>(GetOwningPlayerController(), UserWidgetClass);
		if(InWidget != nullptr)
		{
			InWidget->AddToViewport();
		}

		return InWidget;
	}
	
	void HideWidget(UUserWidget* InWidget)
	{
		if(InWidget != nullptr)
		{
			InWidget->RemoveFromParent();
			InWidget = nullptr;
		}
	}
	
	void ShowHUDWidget();
	void HideHUDWidget();
	void ToggleHUD();

	void ShowInteractionInfoWidget();
	void HideInteractionInfoWidget();

	void RequestLootWidget(const bool bShow);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UPlayerHUDWidget> HUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UInteractionInfoWidget> InteractionInfoWidgetClass;
	
	UPROPERTY()
	UPlayerHUDWidget* HUDWidget;

	UPROPERTY()
	UInteractionInfoWidget* InteractionInfoWidget;

private:
#if !UE_BUILD_SHIPPING
	IConsoleCommand* DevToggleHUDCommand;
#endif
	
};
