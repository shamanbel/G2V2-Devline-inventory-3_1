// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/Animations/BeginInteractNotify.h"

#include "Core/GameCharacter.h"

void UBeginInteractNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if(AGameCharacter* Character = Cast<AGameCharacter>(MeshComp->GetOwner()))
	{
		Character->BeginInteract();
	}
}
