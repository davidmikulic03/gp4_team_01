﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"

#include "Kismet/GameplayStatics.h"

void AMainGameMode::StartGame()
{
	//Handle OnStart things, initialize all necessary systems. Systems can be passed as UPROPERTIES in the BP deriving from this class
	CurrentGameState = GameState::PLAYING;
}

void AMainGameMode::RestartGameOnDeath()
{
	LoadFromLastCheckpoint();
	ResetGameStateOnDeath();
	CurrentGameState = GameState::PLAYING;
}

void AMainGameMode::PauseGame()
{
	UGameplayStatics::SetGamePaused(this, true);
	CurrentGameState = GameState::PAUSED;
}

void AMainGameMode::UnpauseGame()
{
	UGameplayStatics::SetGamePaused(this, false);
	CurrentGameState = GameState::PLAYING;
}

void AMainGameMode::QuitGame() const
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, false);
}

void AMainGameMode::LoadFromLastCheckpoint()
{
	//checkpoint reloading logic
}

void AMainGameMode::ResetGameStateOnDeath()
{
	//restore AI state after death, might be done by having a reference to "BlackboardStateAfterDeath" data asset
}
