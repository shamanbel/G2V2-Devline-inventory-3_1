// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/InteractableActor.h"
#include "LootableActor.generated.h"

class UBoxComponent;

/**
 * 
 */
UCLASS()
class G2VS2_API ALootableActor : public AInteractableActor
{
	GENERATED_BODY()

public:
	ALootableActor();

	virtual void PostInitializeComponents() override;
	
	//~ Begin InteractionInterface Interface
	virtual void BeginInteract_Implementation(UObject* InteractionInstigator, const FHitResult& InteractionHit) override;
	virtual void EndInteract_Implementation(UObject* InteractionInstigator) override;
	virtual void GetInteractionLocation_Implementation(FInteractionLocation& OutLocation) override;
	//~ End InteractionInterface Interface
	
	void NativeBeginLoot(UObject* LootedBy);
	void NativeEndLoot(UObject* LootedBy);
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* InteractionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* InteractionLocation;
	
protected:
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "BeginLoot"))
	void ReceiveBeginLoot();

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "BeginLoot"))
	void ReceiveEndLoot();
};
