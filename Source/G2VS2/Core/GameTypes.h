// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameTypes.generated.h"


/** Please note that this information can be saved with instances
	* also DefaultEngine.ini [/Script/Engine.CollisionProfile] should match with this list **/
#define COLLISION_WEAPON		ECC_GameTraceChannel1
#define COLLISION_PROJECTILE	ECC_GameTraceChannel2
#define COLLISION_INTERACTABLE		ECC_GameTraceChannel3

static FName InteractionTag = FName("Interactive");

UENUM(BlueprintType)
enum class EInteractionPhase : uint8
{
	Begin,
	End
};

UENUM(BlueprintType)
enum class EInteractionPosition : uint8
{
	Up,
	Middle,
	Bottom
};

USTRUCT(BlueprintType)
struct FInteractionLabel
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName InputName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText InteractionText;

	bool IsEmpty() const
	{
		if (InputName.IsNone() == true || InteractionText.IsEmpty() == true)
		{
			return true;
		}

		return false;
	}
};

USTRUCT(BlueprintType)
struct FInteractionLocation
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Location;

	//Whether should character reach point for interact with
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bShouldReach : 1;

	FInteractionLocation() :
	Location(FVector::ZeroVector),
	bShouldReach(false)
	{
	}

	FInteractionLocation(const FVector InLocation, const bool bInShouldReach) :
	Location(InLocation),
	bShouldReach(bInShouldReach)
	{
	}
};

USTRUCT(BlueprintType)
struct FGenericAnimationMontage
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UAnimMontage* Animation;
	
	UPROPERTY(EditAnywhere)
	uint8 bInPlace : 1;

	FGenericAnimationMontage() :
	Animation(nullptr),
	bInPlace(false)
	{
		
	}
};

USTRUCT(BlueprintType)
struct FInteractionSectionSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FName StartSection;

	FInteractionSectionSettings() :
	StartSection(NAME_None)
	{
		
	}
};

USTRUCT(BlueprintType)
struct FInteractionAnimationMontage : public FGenericAnimationMontage
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = General)
	FName BeginInteractSection;

	UPROPERTY(EditAnywhere, Category = General)
	FName EndInteractSection;

	UPROPERTY(EditAnywhere, Category = Additional)
	uint8 bUseLocation : 1;
	
	UPROPERTY(EditAnywhere, Category = Additional, meta = (EditCondition = "bUseLocation"))
	TMap<EInteractionPosition, FName> BeginInteractSections;

	UPROPERTY(EditAnywhere, Category = Additional, meta = (EditCondition = "bUseLocation"))
	TMap<EInteractionPosition, FName> EndInteractSections;

	FInteractionAnimationMontage() :
	BeginInteractSection(NAME_None),
	EndInteractSection(NAME_None),
	bUseLocation(false),
	BeginInteractSections({{EInteractionPosition::Bottom, NAME_None}, {EInteractionPosition::Middle, NAME_None}, {EInteractionPosition::Up, NAME_None}}),
	EndInteractSections({{EInteractionPosition::Bottom, NAME_None}, {EInteractionPosition::Middle, NAME_None}, {EInteractionPosition::Up, NAME_None}})
	{
	}
};

/**
* Class declaration for some static functions
*/
UCLASS()
class G2VS2_API UGameTypes : public UObject
{
	GENERATED_BODY()
};