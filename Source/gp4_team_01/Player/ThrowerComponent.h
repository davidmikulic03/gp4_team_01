// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ThrowableProjectile.h"
#include "PlayerCharacterController.h"
#include "GameFramework/GameModeBase.h"
#include  "ThrowableInventory.h"
#include "ThrowerComponent.generated.h"

struct FPredictProjectilePathPointData;
class AThrowableProjectile;
class UObject;
class APlayerCharacter;
class APlayerCharacterController;
class UThrowableInventory;
class UWorld;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GP4_TEAM_01_API UThrowerComponent : public USceneComponent
{
	GENERATED_BODY()
	//methods
public:	
	UThrowerComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION()
	void Launch();
	UFUNCTION()
	void ResetCooldown();
	UFUNCTION()
	bool IsOnCooldown();
	FPredictProjectilePathResult PredictTrajectory(
		FVector StartLocation,
		FVector LaunchVelocity,
		float ProjectileRadius,
		float MaxSimTime,
		float SimFrequency,
		bool bTracePath);
	UFUNCTION()
	void DrawProjectilePath(FPredictProjectilePathResult PathResult);
	float GetThrowSpeed() { return ThrowSpeed; }
	
protected:
	virtual void BeginPlay() override;
private:	


	//variables
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Thrower")
	float TimeSinceLastThrown = 1000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Thrower")
	float ThrowCooldown = 3.f; //magic number - hardcoded for testing purposes
protected:
	TObjectPtr<APlayerCharacter> PlayerCharacter;
	UPROPERTY(EditDefaultsOnly, Category = "Thrower")
	TSubclassOf<AThrowableProjectile> Throwable;
	UPROPERTY(EditAnywhere, Category = "Thrower")
	float ThrowSpeed = 1500.f;
};
