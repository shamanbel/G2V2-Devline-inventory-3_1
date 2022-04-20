// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataTypes.h"

#include "Interactables/PickupActor.h"

FPickupData::FPickupData() :
UniqueID(FGuid::NewGuid()),
ActorClass(APickupActor::StaticClass()),
bCustomGeometryClass(false)
{
	
}

bool FPickupData::IsValid() const
{
	return UniqueID.IsValid();
}
