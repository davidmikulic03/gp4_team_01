// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "gp4_team_01/Enemies/EnemyBase.h"
#include "gp4_team_01/Systems/NoiseSystem.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "Components/SceneComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "PlayerCharacterController.h"
#include "PetrifyGunComponent.generated.h"

class UWorld;
class AEnemyBase;
class UClass;
class USceneComponent;
class UNiagaraComponent;
class UNoiseDataAsset;
class ANoiseSystem;
class APlayerCharacterController;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GP4_TEAM_01_API UPetrifyGunComponent : public USceneComponent
{
	GENERATED_BODY()
//methods
public:	
	// Sets default values for this component's properties
	UPetrifyGunComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION()
	void TryFirePetrifyGun();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	// Called every frame
//variables
public:
	//muzzle - call muzzle offset as a start point of the linetrace
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gun")
	ANoiseSystem* NoiseSystem;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
	UNoiseDataAsset* NoiseDataAsset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
	float TimeSinceLastShot; //Time that has passed since the player last shot (in Seconds)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gun")
	float ShotCooldown = 5.f; //Mumber of seconds that need to pass between each shot 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
	float TraceLength = 1000.f; //exposed for easy editing, Value for the length of the line trace (default is 1000 cm or 10M)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller")
	APlayerCharacterController* Controller;

	//niagara SFX
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* MuzzleFlash;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* LaserBeam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	float XRotationOffset = -15.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	float YRotationOffset = -15.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	float ZRotationOffset = -15.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	float XPositionOffset = -15.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	float YPositionOffset = -15.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
	float ZPositionOffset = -15.f;
	
private:
protected:
	
		
};
