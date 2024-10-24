// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"

#include "NoiseSystem.h"
#include "PickupManager.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "gp4_team_01/Enemies/EnemyManager.h"

void AMainGameMode::InitGameState() {
	Super::InitGameState();
	
	if(NoiseSystemClass)
		NoiseSystemRef = GetWorld()->SpawnActor<ANoiseSystem>(NoiseSystemClass);
	else
		UE_LOG(LogTemp, Error, TEXT("ERROR: Missing NoiseSystemClass, plug it in the editor!"));

	EnemyManagerRef = GetWorld()->SpawnActor<AEnemyManager>();
	PickupManagerRef = NewObject<UPickupManager>();

	if(!NoiseSystemRef)
		UE_LOG(LogTemp, Error, TEXT("ERROR: Failed to create NoiseSystem"));
}

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
	ShowPauseScreen();
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

void AMainGameMode::LoadLevel(FName LevelName) const {
	UGameplayStatics::OpenLevel(GetWorld(), FName(LevelName));
}

void AMainGameMode::LoadFromLastCheckpoint()
{
	//checkpoint reloading logic
}

void AMainGameMode::ResetGameStateOnDeath()
{
	//restore AI state after death, might be done by having a reference to "BlackboardStateAfterDeath" data asset
}

void AMainGameMode::WinGame()
{
	CurrentGameState = GameState::WIN;
	ShowWinScreen();
}

void AMainGameMode::LoseGame()
{
	CurrentGameState = GameState::LOSE;
	ShowLoseScreen();
}

void AMainGameMode::ShowWinScreen()
{
	if (WinScreenClass && !WinScreenInstance)
	{
		WinScreenInstance = CreateWidget<UUserWidget>(GetWorld(), WinScreenClass);
		if (WinScreenInstance)
		{
			WinScreenInstance->AddToViewport();
		}
	}
}

void AMainGameMode::ShowLoseScreen()
{
	if (LoseScreenClass)
	{
		UUserWidget* LoseScreen = CreateWidget<UUserWidget>(GetWorld(), LoseScreenClass);
		if (LoseScreen)
		{
			LoseScreen->AddToViewport();
		}
	}
}

void AMainGameMode::ShowPauseScreen()
{
	if (PauseScreenClass && !PauseScreenInstance)
	{
		PauseScreenInstance = CreateWidget<UUserWidget>(GetWorld(), PauseScreenClass);
		if (PauseScreenInstance)
		{
			PauseScreenInstance->AddToViewport();
		}
	}
}