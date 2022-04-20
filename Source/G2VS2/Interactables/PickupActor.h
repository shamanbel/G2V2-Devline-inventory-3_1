// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Core/InteractableActor.h"
#include "Data/DataTypes.h"
#include "Engine/DataTable.h"
#include "PickupActor.generated.h"

/**
 * 
 */
UCLASS()
class G2VS2_API APickupActor : public AInteractableActor
{
	GENERATED_BODY()

public:
	APickupActor();

	virtual void OnConstruction(const FTransform& transform) override;
	virtual void PostInitializeComponents() override;
	
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif //
	
	//~ Begin InteractionInterface Interface
	virtual void BeginInteract_Implementation(UObject* InteractionInstigator, const FHitResult& InteractionHit) override;
	virtual void EndInteract_Implementation(UObject* InteractionInstigator) override;
	//~ End InteractionInterface Interface

public:
	void SetData(const FPickupData& InData);
	bool GetData(FPickupData& InData) const;

	bool NativePickup();
	
protected:
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "OnPickup"))
	void ReceivePickup(const bool bSuccess);
	
	void Construct();
	void UpdateGeometry();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* InteractionComponent;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FDataTableRowHandle PickupDataRef;

	FPickupData PickupData;

private:
	bool bPicked;
};
