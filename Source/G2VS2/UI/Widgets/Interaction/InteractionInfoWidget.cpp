// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Interaction/InteractionInfoWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/TextBlock.h"
#include "Interfaces/InteractionInterface.h"
#include "Player/PlayerCharacter.h"

void UInteractionInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if(APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetOwningPlayerPawn()))
	{
		PlayerCharacter->OnFocusedActorChanged.AddUniqueDynamic(this, &UInteractionInfoWidget::OnFocusActorChanged);
	}
}

void UInteractionInfoWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if(ManagedActor.IsValid())
	{
		FVector OnScreenPosition;
		UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPositionWithDistance(GetOwningPlayer(), ManagedActor->GetActorLocation(),  OnScreenPosition, true);
		SetPositionInViewport({OnScreenPosition.X, OnScreenPosition.Y}, false);
	}
	else if(IsVisible())
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
}

void UInteractionInfoWidget::NativeDestruct()
{
	if(APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetOwningPlayerPawn()))
	{
		PlayerCharacter->OnFocusedActorChanged.RemoveAll(this);
	}
	Super::NativeDestruct();
}

void UInteractionInfoWidget::OnFocusActorChanged(AActor* NewFocus)
{
	ManagedActor = NewFocus;
	if(ManagedActor.IsValid() == false)
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		FInteractionLabel InteractionLabel;
		IInteractionInterface::Execute_GetInteractionLabel(ManagedActor.Get(), InteractionLabel);
		InteractionText->SetText(InteractionLabel.InteractionText);
		SetVisibility(ESlateVisibility::SelfHitTestInvisible);

		FVector OnScreenPosition;
		UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPositionWithDistance(GetOwningPlayer(), ManagedActor->GetActorLocation(),  OnScreenPosition, true);
		SetPositionInViewport({OnScreenPosition.X, OnScreenPosition.Y}, false);
	}
}
