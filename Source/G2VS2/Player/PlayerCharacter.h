// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/GameCharacter.h"
#include "PlayerCharacter.generated.h"

class UInventoryComponent;
class USpringArmComponent;
class UCameraComponent;
class APlayerCharacter;

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FFocusedActorChangedSignature, APlayerCharacter, OnFocusedActorChanged, AActor*, NewFocusedActor);
/**
 * 
 */
UCLASS()
class G2VS2_API APlayerCharacter : public AGameCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	virtual void PostInitializeComponents() override;
	
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetFocusedActor(AActor* NewActor);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "Health")
		float Health;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void MoveForward(float Value);
	void MoveRight(float Value);
	
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	void PlayerInteract();

	UFUNCTION(BlueprintCallable, Category = "Items")
	void UseItem(class UItem* Item);

	UFUNCTION()
	void OnRequestedOrientationCompleted();
	
public:
	FFocusedActorChangedSignature OnFocusedActorChanged;
	
protected:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* ThirdPersonCameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* ThirdPersonCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	class UInventoryComponent* Inventory;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Interaction)
	float InteractionDistance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Interaction)
	float CheckFocusTime;
	
protected:
	void CheckFocus();
	
protected:
	TWeakObjectPtr<AActor> FocusedActor;

private:
	float CheckFocusTimer;
	bool bRequestedOrientation;
	FRotator RequestedRotation;
};
