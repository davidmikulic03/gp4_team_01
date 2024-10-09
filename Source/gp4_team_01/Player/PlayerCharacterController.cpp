// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();

	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}

}