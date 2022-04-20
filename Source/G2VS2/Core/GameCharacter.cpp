// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/GameCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/InteractionInterface.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AGameCharacter::AGameCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

bool AGameCharacter::PlayInteractionMontage(const FGameplayTag& AnimationID, const EInteractionPhase InInteractionPhase)
{
	if(InteractionAnimationSet.Contains(AnimationID) == false)
	{
		return false;
	}

	UAnimMontage* MontageToPlay = InteractionAnimationSet[AnimationID].Animation;
	if(MontageToPlay == nullptr)
	{
		return false;
	}

	if(InteractionAnimationSet[AnimationID].bInPlace == true)
	{
		GetCharacterMovement()->SetMovementMode(MOVE_None);
	}
	
	FName StartSection = NAME_None;
	
	if(InteractionAnimationSet[AnimationID].bUseLocation == true)
	{
		EInteractionPosition ToPosition = EInteractionPosition::Middle;
	
		if(InteractingWith.IsValid())
		{
			FInteractionLocation InteractionLocation;
			IInteractionInterface::Execute_GetInteractionLocation(InteractingWith.Get(), InteractionLocation);
			ToPosition = CalcInteractionPosition(InteractionLocation);
		}
		switch (InInteractionPhase)
		{
		case EInteractionPhase::Begin:
			StartSection = InteractionAnimationSet[AnimationID].BeginInteractSections[ToPosition];
			break;
		case EInteractionPhase::End:
			StartSection = InteractionAnimationSet[AnimationID].EndInteractSections[ToPosition];
			break;
		default: ;
		}
	}
	else
	{
		switch (InInteractionPhase)
		{
		case EInteractionPhase::Begin:
			StartSection = InteractionAnimationSet[AnimationID].BeginInteractSection;
			break;
		case EInteractionPhase::End:
			StartSection = InteractionAnimationSet[AnimationID].EndInteractSection;
			break;
		default: ;
		}
	}

	if(StartSection == NAME_None)
	{
		StopAnimMontage(InteractionAnimationSet[AnimationID].Animation);
		return false;
	}

	if(GetMesh()->GetAnimInstance()->GetCurrentActiveMontage() == MontageToPlay)
	{
		GetMesh()->GetAnimInstance()->Montage_JumpToSection(StartSection, MontageToPlay);
	}
	else
	{
		PlayAnimMontage(MontageToPlay, 1.f, StartSection);
		PlayedAnimationID = AnimationID;
		GetMesh()->GetAnimInstance()->OnMontageEnded.AddUniqueDynamic(this, &AGameCharacter::OnInteractionMontageCompleted);
	}
	
	return true;
}

EInteractionPosition AGameCharacter::CalcInteractionPosition(const FInteractionLocation& InteractionLocation) const
{
	const float CharacterHalfHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	const FVector CharacterLocation = GetCapsuleComponent()->GetComponentLocation();
	const float PositionsDiff = InteractionLocation.Location.Z - CharacterLocation.Z;
	if(PositionsDiff > (CharacterHalfHeight/2))
	{
		return EInteractionPosition::Up;
	}
	else if(PositionsDiff < -(CharacterHalfHeight/2))
	{
		return EInteractionPosition::Bottom;
	}

	return EInteractionPosition::Middle;
}

void AGameCharacter::OnInteractionMontageCompleted(UAnimMontage* Montage, bool bInterrupted)
{
	GetMesh()->GetAnimInstance()->OnMontageEnded.RemoveAll(this);
	EndInteract();

}

// Called every frame
void AGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameCharacter::BeginInteract()
{
	if(InteractingWith.IsValid())
	{
		IInteractionInterface::Execute_BeginInteract(InteractingWith.Get(), this, InteractionHitInfo);
		GetCharacterMovement()->SetMovementMode(MOVE_None);
	}
	
	OnInteractionChanged.Broadcast(InteractingWith.Get(), CurrentInteractionPhase);
}

void AGameCharacter::EndInteract()
{
	//End interaction
	if(InteractingWith.IsValid())
	{
		IInteractionInterface::Execute_EndInteract(InteractingWith.Get(), this);
	}
	
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	OnInteractionChanged.Broadcast(InteractingWith.Get(), CurrentInteractionPhase);
	
	bInteracting = false;
	InteractingWith = nullptr;
}

void AGameCharacter::Interact(AActor* ToInteractWith)
{
	if(RequestBeginInteract(ToInteractWith) == true)
	{
		RequestEndInteract();
	}
}

bool AGameCharacter::RequestBeginInteract(AActor* ToInteractWith)
{
	if(bInteracting == true)
	{
		return false;
	}
	
	bInteracting = true;
	InteractingWith = ToInteractWith;
	
	FGameplayTag InteractType;
	IInteractionInterface::Execute_GetInteractionType(InteractingWith.Get(), InteractType);

	CurrentInteractionPhase = EInteractionPhase::Begin;
	
	//If we have animation lets provide control there
	if(PlayInteractionMontage(InteractType, CurrentInteractionPhase) == true)
	{
		return false;
	}

	//If we do not have animation just begin interaction immediately
	BeginInteract();

	return true;
}

bool AGameCharacter::RequestEndInteract()
{
	FGameplayTag InteractType;
	IInteractionInterface::Execute_GetInteractionType(InteractingWith.Get(), InteractType);

	CurrentInteractionPhase = EInteractionPhase::End;
	
	//Provide control to animation if we have one
	if(PlayInteractionMontage(InteractType, CurrentInteractionPhase) == true)
	{
		return false;
	}
	
	EndInteract();

	return true;
}

bool AGameCharacter::IsInteracting() const
{
	return bInteracting;
}

