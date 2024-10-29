// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"

#include "MainGameMode.generated.h"

class UPickupManager;
class AEnemyManager;
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
	void LoadLevel(FName LevelName) const;

	UFUNCTION(BlueprintCallable)
	void WinGame();

	UFUNCTION(BlueprintCallable)
	void LoseGame();

	void RestartGameOnDeath();

public:
	enum GameState GetCurrentGameState() const { return CurrentGameState; };
	
	UFUNCTION(BlueprintCallable)
	ANoiseSystem* GetNoiseSystemRef() { return  NoiseSystemRef; };
	UFUNCTION(BlueprintCallable)
	AEnemyManager* GetEnemyManagerRef() const { return EnemyManagerRef; };
	UFUNCTION(BlueprintCallable)
	UPickupManager* GetPickupManagerRef() const { return PickupManagerRef; };

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> WinScreenClass;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> LoseScreenClass;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PauseScreenClass;

private:
	void LoadFromLastCheckpoint();
	void ResetGameStateOnDeath();
	void ShowWinScreen();
	void ShowLoseScreen();
	void ShowPauseScreen();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Systems", meta = (AllowPrivateAccess = true))
	TSubclassOf<ANoiseSystem> NoiseSystemClass = nullptr;
	
	enum GameState CurrentGameState;

	UPROPERTY()
	TObjectPtr<ANoiseSystem> NoiseSystemRef = nullptr;

	UPROPERTY()
	AEnemyManager* EnemyManagerRef = nullptr;

	UPROPERTY()
	UPickupManager* PickupManagerRef = nullptr;

private:
	UUserWidget* WinScreenInstance;
	UUserWidget* LoseScreenInstance;
	UUserWidget* PauseScreenInstance;

};

