// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactables/PickupActor.h"
#include "Components/BoxComponent.h"
#include "Core/InteractionSettings.h"

APickupActor::APickupActor()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(MeshComponent);

	InteractionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionComponent->SetupAttachment(MeshComponent);
	InteractionComponent->SetCanEverAffectNavigation(false);
	InteractionComponent->SetCollisionObjectType(COLLISION_INTERACTABLE);
}

void APickupActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	Construct();
}

void APickupActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if(const UInteractionSettings* InteractionSettings = Cast<UInteractionSettings>(UInteractionSettings::StaticClass()->GetDefaultObject()))
	{
		InteractionType = InteractionSettings->DefaultPickupTag;
	}
}

#if WITH_EDITOR
void APickupActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if(PropertyChangedEvent.GetPropertyName().IsEqual("PickupData"))
	{
		Construct();
		MarkPackageDirty();
	}
}
#endif

void APickupActor::BeginInteract_Implementation(UObject* InteractionInstigator, const FHitResult& InteractionHit)
{
	Super::BeginInteract_Implementation(InteractionInstigator, InteractionHit);
	// Item successfully added 
	bPicked = NativePickup();
	if(bPicked == true)
	{
		GetRootComponent()->SetVisibility(false, true);
	}
}

void APickupActor::EndInteract_Implementation(UObject* InteractionInstigator)
{
	Super::EndInteract_Implementation(InteractionInstigator);
	if(bPicked)
	{
		Destroy();
	}
}

void APickupActor::SetData(const FPickupData& InData)
{
	PickupData = InData;
	//TODO: Implement deferred loading
	MeshComponent->SetStaticMesh(PickupData.WorldMesh.LoadSynchronous());
}

bool APickupActor::GetData(FPickupData& InData) const
{
	InData = PickupData;
	return PickupData.IsValid();
}

bool APickupActor::NativePickup()
{
	//TODO: Implement on pickup when inventory will be implemented
	bool RetValue = true;
	ReceivePickup(RetValue);
	return RetValue;
}


void APickupActor::Construct()
{
	if(PickupDataRef.IsNull() == false)
	{
		if(const FPickupData* DataRow = PickupDataRef.GetRow<FPickupData>("General"))
		{
			SetData(*DataRow);
		}
	}
	else
	{
		SetData({});
	}
		
	UpdateGeometry();
}

void APickupActor::UpdateGeometry()
{

	//That means we have pickup with custom geometry, so do not update mesh and extends
	if(PickupData.bCustomGeometryClass == true)
	{
		return;
	}
	
	UStaticMesh* CurrentMesh = MeshComponent->GetStaticMesh();
	if (CurrentMesh != nullptr
		&& CurrentMesh->GetBounds().BoxExtent != InteractionComponent->GetUnscaledBoxExtent())
	{
		InteractionComponent->SetBoxExtent(CurrentMesh->GetBounds().BoxExtent);
		InteractionComponent->SetRelativeLocation(CurrentMesh->GetBounds().Origin);
		InteractionComponent->MarkRenderStateDirty();
	}
	else if ( CurrentMesh == nullptr )
	{
		InteractionComponent->ResetRelativeTransform();
	}
}
