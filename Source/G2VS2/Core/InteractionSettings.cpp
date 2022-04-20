// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/InteractionSettings.h"

UInteractionSettings::UInteractionSettings()
{
	DefaultInteractionLabel.InputName = "Interact";
	DefaultInteractionLabel.InteractionText = FText::FromString("Interact");
}

void UInteractionSettings::PostInitProperties()
{
	Super::PostInitProperties();
}
