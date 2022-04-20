// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/LootableActor.h"

#include "Components/BoxComponent.h"
#include "Core/InteractionSettings.h"
#include "Player/GamePlayerController.h"
#include "Player/PlayerCharacter.h"

ALootableActor::ALootableActor()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(MeshComponent);

	InteractionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionComponent->SetupAttachment(MeshComponent);
	InteractionComponent->SetCanEverAffectNavigation(false);
	InteractionComponent->SetCollisionObjectType(COLLISION_INTERACTABLE);

	InteractionLocation = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Interactionlocation"));
	InteractionLocation->SetupAttachment(MeshComponent);
}

void ALootableActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if(const UInteractionSettings* InteractionSettings = Cast<UInteractionSettings>(UInteractionSettings::StaticClass()->GetDefaultObject()))
	{
		InteractionType = InteractionSettings->DefaultLootTag;
	}
}

void ALootableActor::BeginInteract_Implementation(UObject* InteractionInstigator, const FHitResult& InteractionHit)
{
	Super::BeginInteract_Implementation(InteractionInstigator, InteractionHit);
	NativeBeginLoot(InteractionInstigator);
}

void ALootableActor::EndInteract_Implementation(UObject* InteractionInstigator)
{
	Super::EndInteract_Implementation(InteractionInstigator);
}

void ALootableActor::GetInteractionLocation_Implementation(FInteractionLocation& OutLocation)
{
	OutLocation = {InteractionLocation->GetComponentLocation(), true};
}

void ALootableActor::NativeBeginLoot(UObject* LootedBy)
{
	ReceiveBeginLoot();
}

void ALootableActor::NativeEndLoot(UObject* LootedBy)
{
	ReceiveEndLoot();
}
