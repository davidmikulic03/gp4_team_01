// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"

#include "MainGameMode.generated.h"

class ANoiseSystem;

enum class GameState : uint8
{
	NONE = 0,
	PLAYING,
	PAUSED,
	WIN,
	LOSE
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

	UFUNCTION(BlueprintCallable)
	void WinGame();

	UFUNCTION(BlueprintCallable)
	void LoseGame();

	void RestartGameOnDeath();

public:
	enum GameState GetCurrentGameState() const { return CurrentGameState; };
	
	UFUNCTION(BlueprintCallable)
	ANoiseSystem* GetNoiseSystemRef() { return  NoiseSystemRef; };

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> WinScreenClass;
	TSubclassOf<UUserWidget> LoseScreenClass;


private:
	void LoadFromLastCheckpoint();
	void ResetGameStateOnDeath();
	void ShowWinScreen();
	void ShowLoseScreen();
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Systems", meta = (AllowPrivateAccess = true))
	TSubclassOf<ANoiseSystem> NoiseSystemClass = nullptr;
	
	inline static TObjectPtr<ANoiseSystem> NoiseSystemRef = nullptr;

private:
	enum GameState CurrentGameState;
	UUserWidget* WinScreenInstance;
	UUserWidget* LoseScreenInstance;

};

