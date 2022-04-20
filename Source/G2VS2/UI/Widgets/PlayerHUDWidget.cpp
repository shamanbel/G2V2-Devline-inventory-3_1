// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/PlayerHUDWidget.h"

#include "Core/InteractionSettings.h"
#include "Interaction/InteractionInfoWidget.h"
#include "Interaction/LootWidget.h"
#include "Interfaces/InteractionInterface.h"
#include "Player/GamePlayerController.h"
#include "Player/PlayerCharacter.h"

void UPlayerHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	LootWidget->SetVisibility(ESlateVisibility::Hidden);
	if(APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetOwningPlayerPawn()))
	{
		PlayerCharacter->OnInteractionChanged.AddUniqueDynamic(this, &UPlayerHUDWidget::OnInteractActorChanged);
	}
}

void UPlayerHUDWidget::NativeDestruct()
{
	if(APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetOwningPlayerPawn()))
	{
		PlayerCharacter->OnInteractionChanged.RemoveAll(this);
	}
	Super::NativeDestruct();
}

void UPlayerHUDWidget::OnInteractActorChanged(AActor* NewInteract, const EInteractionPhase InteractionPhase)
{
	if(NewInteract == nullptr || InteractionPhase == EInteractionPhase::End)
	{
		ShowLootWidget(false);
		if(AGamePlayerController* PlayerController = Cast<AGamePlayerController>(GetOwningPlayer()))
		{
			PlayerController->SetPlayerGameInput();
		}
		return;
	}

	FGameplayTag LootTagType = FGameplayTag::EmptyTag;
	
	if(const UInteractionSettings* InteractionSettings = Cast<UInteractionSettings>(UInteractionSettings::StaticClass()->GetDefaultObject()))
	{
		LootTagType = InteractionSettings->DefaultLootTag;
	}

	FGameplayTag InteractType;
	IInteractionInterface::Execute_GetInteractionType(NewInteract, InteractType);
	
	if(LootTagType == InteractType && InteractionPhase == EInteractionPhase::Begin)
	{
		ShowLootWidget(true);
		if(AGamePlayerController* PlayerController = Cast<AGamePlayerController>(GetOwningPlayer()))
		{
			PlayerController->SetPlayerUIInput();
		}
	}
}

void UPlayerHUDWidget::ShowLootWidget(const bool bShow)
{
	const ESlateVisibility NewVisibility = bShow == true ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Hidden;
	LootWidget->SetVisibility(NewVisibility);
}
