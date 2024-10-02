// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"

enum class GameState : uint8
{
	NONE = 0,
	PLAYING,
	PAUSED
};

UCLASS(Abstract)
class GP4_TEAM_01_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void StartGame();
	
	UFUNCTION(BlueprintCallable)
	void PauseGame();
	
	UFUNCTION(BlueprintCallable)
	void UnpauseGame();

	UFUNCTION(BlueprintCallable)
	void QuitGame() const;

	void RestartGameOnDeath();

public:
	enum GameState GetCurrentGameState() const { return CurrentGameState; };

private:
	void LoadFromLastCheckpoint();
	void ResetGameStateOnDeath();
	
private:
	enum GameState CurrentGameState;
};
