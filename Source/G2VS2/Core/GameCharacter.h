// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameTypes.h"
#include "GameFramework/Character.h"
#include "GameCharacter.generated.h"

class AGameCharacter;

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_TwoParams(FInteractionChangedSignature, AGameCharacter, OnInteractionChanged, AActor*, NewInteractionActor, const EInteractionPhase, InteractionPhase);

UCLASS()
class G2VS2_API AGameCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGameCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginInteract();

	virtual void EndInteract();
	
	virtual void Interact(AActor* ToInteractWith);

	bool RequestBeginInteract(AActor* ToInteractWith);

	bool RequestEndInteract();

	bool IsInteracting() const;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool PlayInteractionMontage(const FGameplayTag& AnimationID, const EInteractionPhase InInteractionPhase);
	
	EInteractionPosition CalcInteractionPosition(const FInteractionLocation& InteractionLocation) const;
	
	UFUNCTION()
	void OnInteractionMontageCompleted(UAnimMontage* Montage, bool bInterrupted);

public:
	FInteractionChangedSignature OnInteractionChanged;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category=Animation)
	TMap<FGameplayTag, FInteractionAnimationMontage> InteractionAnimationSet;
	
	UPROPERTY(EditDefaultsOnly, Category=Animation)
	TMap<FGameplayTag, FGenericAnimationMontage> GenericAnimationSet;

protected:
	TWeakObjectPtr<AActor> InteractingWith;
	
	FHitResult InteractionHitInfo;
	
private:
	bool bInteracting;
	EInteractionPhase CurrentInteractionPhase;
	FGameplayTag PlayedAnimationID;
};
