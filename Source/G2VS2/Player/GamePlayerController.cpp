// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GamePlayerController.h"

#include "PlayerCharacter.h"
#include "UI/InGameHUD.h"

void AGamePlayerController::SetPlayerUIInput()
{
	SetInputMode(FInputModeUIOnly());
	SetShowMouseCursor(true);
}

void AGamePlayerController::SetPlayerGameInput()
{
	SetInputMode(FInputModeGameOnly());
	SetShowMouseCursor(false);
}
