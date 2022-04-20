// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGameHUD.h"

#include "Blueprint/UserWidget.h"
#if !UE_BUILD_SHIPPING
#include "HAL/ConsoleManager.h"
#endif
#include "Widgets/PlayerHUDWidget.h"
#include "Widgets/Interaction/InteractionInfoWidget.h"

AInGameHUD::AInGameHUD()
{
	
}

void AInGameHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();
#if !UE_BUILD_SHIPPING
	if(DevToggleHUDCommand == nullptr)
	{
		//Register development command to cleanup saved data
		DevToggleHUDCommand = FConsoleManager::Get().RegisterConsoleCommand(TEXT("ToggleHUD"), TEXT("Show/Hide player hud widget"), FConsoleCommandDelegate::CreateLambda([this](){ ToggleHUD(); }), ECVF_Default);
	}
#endif
}

void AInGameHUD::BeginPlay()
{
	Super::BeginPlay();
	ShowHUDWidget();
	ShowInteractionInfoWidget();
}

void AInGameHUD::ShowHUDWidget()
{
	if(HUDWidget == nullptr)
	{
		HUDWidget = ShowWidget<UPlayerHUDWidget>(HUDWidgetClass);	
	}
}

void AInGameHUD::HideHUDWidget()
{
	HideWidget(HUDWidget);
}

void AInGameHUD::ToggleHUD()
{
	if (HUDWidget == nullptr)
	{
		ShowHUDWidget();
	}
	else
	{
		HideHUDWidget();
	}
}

void AInGameHUD::ShowInteractionInfoWidget()
{
	if(InteractionInfoWidget == nullptr)
	{
		InteractionInfoWidget = ShowWidget<UInteractionInfoWidget>(InteractionInfoWidgetClass);
	}
	
	if(InteractionInfoWidget != nullptr)
	{
		//Hidden by default
		InteractionInfoWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AInGameHUD::HideInteractionInfoWidget()
{
	HideWidget(InteractionInfoWidget);
}

void AInGameHUD::RequestLootWidget(const bool bShow)
{
	if(HUDWidget != nullptr)
	{
		HUDWidget->ShowLootWidget(bShow);
	}
}

