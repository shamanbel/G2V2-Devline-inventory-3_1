// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LockComponent.generated.h"


UENUM()
enum class ELockState : uint8
{
	Locked,
	Unlocked,
	Broken
};

UENUM()
enum class ELockPickSequenceType : uint8
{
	Left,
	Right,
	Up,
	Down
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class G2VS2_API ULockComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULockComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	void SetState(const ELockState NewState);
	ELockState GetState() const;

	UFUNCTION(BlueprintPure)
	bool IsLocked() const;

	UFUNCTION(BlueprintPure)
	bool CanBePickLock(const int32 InSkillLevel) const;

	UFUNCTION(BlueprintCallable)
	void ResetLockPickPosition();

	UFUNCTION(BlueprintCallable)
	bool ReceiveLockPickSignal(const ELockPickSequenceType InSignal);

	UFUNCTION(BlueprintPure)
	int32 GetKeyID() const;

public:	
	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "Date Time Updated"))
	void OnLockStateChanged(const ELockState NewLockState);

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "Date Time Updated"))
	void OnPickLockAttemptValid();

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "Date Time Updated"))
	void OnPickLockAttemptInvalid();
	
protected:
	//State of lock
	UPROPERTY(Category = Lock, EditAnywhere)
	ELockState LockState;

	//ID of the key to open this lock
	UPROPERTY(Category = Lock, EditAnywhere)
	int32 KeyID;
	
	UPROPERTY(Category = Lock, EditAnywhere)
	int32 SkillLevel;
	
	//Can be opened by key only
	UPROPERTY(Category = Lock, EditAnywhere)
	bool bKeyOnly;
	
	//Sequence required to pick this lock 
	UPROPERTY(Category = Lock, EditAnywhere, meta = (EditCondition = "!bKeyOnly"))
	TArray<ELockPickSequenceType> PickLockSequence;

private:
	int32 LockPickPosition;
};
