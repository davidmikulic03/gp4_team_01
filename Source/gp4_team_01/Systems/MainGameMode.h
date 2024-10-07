// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"

class ANoiseSystem;

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
	virtual void InitGameState() override;

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
	
	UFUNCTION(BlueprintCallable)
	ANoiseSystem* GetNoiseSystemRef() { return  NoiseSystemRef; }; 

private:
	void LoadFromLastCheckpoint();
	void ResetGameStateOnDeath();
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Systems", meta = (AllowPrivateAccess = true))
	TSubclassOf<ANoiseSystem> NoiseSystemClass = nullptr;
	
	inline static TObjectPtr<ANoiseSystem> NoiseSystemRef = nullptr;
};
