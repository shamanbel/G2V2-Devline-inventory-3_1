// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/InteractableActor.h"
#include "GameTypes.h"
#include "InteractionSettings.h"

// Sets default values
AInteractableActor::AInteractableActor()
{
 	// False by default for performance purposes
	PrimaryActorTick.bCanEverTick = false;
	Tags.AddUnique(InteractionTag);
}

void AInteractableActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if(InteractionLabel.IsEmpty())
	{
		if(const UInteractionSettings* InteractionSettings = Cast<UInteractionSettings>(UInteractionSettings::StaticClass()->GetDefaultObject()))
		{
			InteractionLabel = InteractionSettings->DefaultInteractionLabel;
		}
	}
}

void AInteractableActor::GetInteractionLabel_Implementation(FInteractionLabel& OutLabel)
{
	OutLabel = InteractionLabel;
}

bool AInteractableActor::CanInteract_Implementation() const
{
	return ActorHasTag(InteractionTag);
}

void AInteractableActor::GetInteractionType_Implementation(FGameplayTag& Out)
{
	Out = InteractionType;
}

void AInteractableActor::GetInteractionLocation_Implementation(FInteractionLocation& OutLocation)
{
	OutLocation = {GetRootComponent()->GetComponentLocation(), false};
}

void AInteractableActor::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer = GameplayTags;
}


