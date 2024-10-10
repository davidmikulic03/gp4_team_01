// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ThrowableProjectile.h"
#include "PlayerCharacterController.h"
#include "GameFramework/GameModeBase.h"
<<<<<<<< Updated upstream:Source/gp4_team_01/Player/ThrowerComponent.h
#include  "ThrowableInventory.h"
#include "ThrowerComponent.generated.h"
========
#include  "gp4_team_01/Public/ThrowableInventory.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "ACThrowerComponent.generated.h"
>>>>>>>> Stashed changes:Source/gp4_team_01/Player/ACThrowerComponent.h

class AThrowableProjectile;
class UObject;
class APlayerCharacter;
class APlayerCharacterController;
class UThrowableInventory;
class UWorld;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
<<<<<<<< Updated upstream:Source/gp4_team_01/Player/ThrowerComponent.h
class GP4_TEAM_01_API UThrowerComponent : public UActorComponent
========
class GP4_TEAM_01_API UACThrowerComponent : public UActorComponent
>>>>>>>> Stashed changes:Source/gp4_team_01/Player/ACThrowerComponent.h
{
	GENERATED_BODY()
	//methods
public:	
<<<<<<<< Updated upstream:Source/gp4_team_01/Player/ThrowerComponent.h
	UThrowerComponent();
========
	UACThrowerComponent();
>>>>>>>> Stashed changes:Source/gp4_team_01/Player/ACThrowerComponent.h
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION()
	void Launch();
	UFUNCTION()
	void ResetCooldown();
	UFUNCTION()
	bool IsOnCooldown();
	TArray<FPredictProjectilePathPointData> PreditctTrajectory(
		FVector StartLocation,
		FVector LaunchVelocity,
		float ProjectileRadius,
		float MaxSimTime,
		float SimFrequency,
		bool bTracePath);
	UFUNCTION()
	void DrawProjectilePath();
protected:
	virtual void BeginPlay() override;
private:	


	//variables
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Thrower")
	float TimeSinceLastThrown = 1000.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Thrower")
	float ThrowCooldown = 3.f;
protected:
private:
	TObjectPtr<APlayerCharacter> PlayerCharacter;
	UPROPERTY(EditDefaultsOnly, Category = "Thrower")
	TSubclassOf<AThrowableProjectile> Throwable;
	UPROPERTY(EditAnywhere, Category = "Thrower")
	FVector MuzzleOffset;
	AGameModeBase* GameMode;
	UPROPERTY(EditAnywhere, Category = "Thrower")
	float ThrowAngle = 30.f;
};
