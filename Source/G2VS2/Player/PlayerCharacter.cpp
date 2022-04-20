// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Core/GameTypes.h"
#include "Core/InteractionSettings.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interfaces/InteractionInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Windows/Accessibility/WindowsUIABaseProvider.h"
#include "inventorySystem/Item.h"
#include "inventorySystem/InventoryComponent.h"

APlayerCharacter::APlayerCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	ThirdPersonCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	ThirdPersonCameraBoom->SetupAttachment(RootComponent);
	ThirdPersonCameraBoom->TargetArmLength = 300.0f; 	
	ThirdPersonCameraBoom->bUsePawnControlRotation = true; 

	// Create a follow camera
	ThirdPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	ThirdPersonCamera->SetupAttachment(ThirdPersonCameraBoom, USpringArmComponent::SocketName); 
	ThirdPersonCamera->bUsePawnControlRotation = false;

	Inventory = CreateDefaultSubobject<UInventoryComponent>("Inventory");
	Inventory->Capacity = 20;
	
	Health = 100.0f;
	InteractionDistance = 800.f;
	CheckFocusTime = 0.5f;
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if(const UInteractionSettings* InteractionSettings = Cast<UInteractionSettings>(UInteractionSettings::StaticClass()->GetDefaultObject()))
	{
		InteractionDistance = InteractionSettings->InteractionDistance;
		CheckFocusTime = InteractionSettings->CheckFocusTime;
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	//TODO: Uncomment when blueprint actions will be moved here 
	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	//PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	
	//PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	//PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	//PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	//PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &APlayerCharacter::PlayerInteract);
}

void APlayerCharacter::UseItem(UItem* Item)
{
	if (Item)
	{
		Item->Use(this);
		Item->On_Use(this);
	}

}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if( CheckFocusTimer <= 0 )
	{
		CheckFocus();
		CheckFocusTimer = CheckFocusTime;
	}
	else
	{
		CheckFocusTimer -= DeltaTime;
	}

	if(bRequestedOrientation == true)
	{
		float toRot = 100*DeltaTime;
		RequestedRotation.Yaw = RequestedRotation.Yaw - toRot;
		if(RequestedRotation.Yaw <= 0)
		{
			OnRequestedOrientationCompleted();
			bRequestedOrientation = false;
		}
		//AddControllerYawInput(toRot);
		AddActorLocalRotation(FRotator(0, toRot, 0));
	}
}

void APlayerCharacter::SetFocusedActor(AActor* NewActor)
{

	if(FocusedActor == NewActor)
	{
		return;
	}
	
	if(FocusedActor.IsValid())
	{
		IInteractionInterface::Execute_LostFocus(FocusedActor.Get(), this);
	}

	FocusedActor = NewActor;
	OnFocusedActorChanged.Broadcast(FocusedActor.Get());

	if(FocusedActor.IsValid())
	{
		IInteractionInterface::Execute_GainFocus(FocusedActor.Get(), this);
	}
}

void APlayerCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::CheckFocus()
{
	//Just pass if player already interacting with something
	if(IsInteracting())
	{
		SetFocusedActor(nullptr);
		return;
	}
	
	const FVector CurrentLocation = GetActorLocation();
	const float TraceHalfHeight = GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	TArray<FHitResult> OutHits;
	AActor* TestActor = nullptr;
	
	if(UKismetSystemLibrary::CapsuleTraceMultiForObjects(this, CurrentLocation, CurrentLocation,
		InteractionDistance, TraceHalfHeight, {UEngineTypes::ConvertToObjectType(COLLISION_INTERACTABLE)}, true, {}, EDrawDebugTrace::None, OutHits, true) == true)
	{
		for(const FHitResult& HitResult : OutHits)
		{
			//Double check that actor implements interaction interface 
			if(HitResult.GetActor()->Implements<UInteractionInterface>() == false)
			{
				continue;
			}

			if(IInteractionInterface::Execute_CanInteract(HitResult.GetActor()) == false)
			{
				continue;
			}

			//TODO: Add case for objects that should be interacted in special direction
			//Check that we looking in direction to interactable and angle is valid
			const FVector DirectionVector = UKismetMathLibrary::GetDirectionUnitVector(CurrentLocation,HitResult.Actor->GetActorLocation());
			if(FVector::DotProduct(DirectionVector, GetBaseAimRotation().Vector()) < 0.6)
			{
				continue;
			}
			
			if(TestActor == nullptr)
			{
				TestActor = HitResult.GetActor();
			}
			else
			{
				//Take nearest
				if(TestActor->GetSquaredHorizontalDistanceTo(this) > HitResult.GetActor()->GetSquaredHorizontalDistanceTo(this))
				{
					TestActor = HitResult.GetActor();
				}
			}
		}
	}

	SetFocusedActor(TestActor);
}

void APlayerCharacter::PlayerInteract()
{
	if(FocusedActor.IsValid() == false)
	{
		return;
	}

	//TODO: Should be reworked depending by animation BP
	const FRotator FaceTo = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), FocusedActor->GetActorLocation());
	GetCharacterMovement()->SetMovementMode(MOVE_None);
	SetActorRotation(FRotator(GetActorRotation().Pitch, FaceTo.Yaw, GetActorRotation().Roll));
	OnRequestedOrientationCompleted();
}

void APlayerCharacter::OnRequestedOrientationCompleted()
{
	Interact(FocusedActor.Get());
	SetFocusedActor(nullptr);
}
