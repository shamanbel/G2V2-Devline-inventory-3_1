// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Interaction/LootWidget.h"
#include "Components/Button.h"
#include "Player/GamePlayerController.h"
#include "Player/PlayerCharacter.h"

void ULootWidget::NativeConstruct()
{
	Super::NativeConstruct();
	CloseButton->OnClicked.AddUniqueDynamic(this, &ULootWidget::OnCloseButtonPressed);
}

void ULootWidget::NativeDestruct()
{
	CloseButton->OnClicked.RemoveAll(this);
	Super::NativeDestruct();
}

void ULootWidget::OnCloseButtonPressed()
{
	if(APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetOwningPlayerPawn()))
	{
		PlayerCharacter->RequestEndInteract();
	}
}
