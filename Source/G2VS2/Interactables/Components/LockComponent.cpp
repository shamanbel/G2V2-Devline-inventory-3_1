// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/Components/LockComponent.h"

// Sets default values for this component's properties
ULockComponent::ULockComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	LockState = ELockState::Unlocked;
	bKeyOnly = false;
	PickLockSequence = {ELockPickSequenceType::Left, ELockPickSequenceType::Right};

	LockPickPosition = 0;

	KeyID = INDEX_NONE;
}


// Called when the game starts
void ULockComponent::BeginPlay()
{
	Super::BeginPlay();
}

void ULockComponent::SetState(const ELockState NewState)
{
	LockState = NewState;
	OnLockStateChanged(LockState);
}

ELockState ULockComponent::GetState() const
{
	return LockState;
}

bool ULockComponent::IsLocked() const
{
	return LockState == ELockState::Locked;
}

bool ULockComponent::CanBePickLock(const int32 InSkillLevel) const
{
	return bKeyOnly == false && LockState != ELockState::Broken && InSkillLevel >= SkillLevel;
}

void ULockComponent::ResetLockPickPosition()
{
	LockPickPosition = 0;
}

bool ULockComponent::ReceiveLockPickSignal(const ELockPickSequenceType InSignal)
{
	if(PickLockSequence[LockPickPosition] != InSignal)
	{
		OnPickLockAttemptInvalid();
		ResetLockPickPosition();
		return false;
	}
	
	if(LockPickPosition == PickLockSequence.Num()-1)
	{
		SetState(ELockState::Unlocked);
	}
	else
	{
		OnPickLockAttemptValid();
		LockPickPosition++;
	}
	
	return true;
}

int32 ULockComponent::GetKeyID() const
{
	return KeyID;
}



