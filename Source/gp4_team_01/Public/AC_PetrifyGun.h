// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "gp4_team_01/Enemies/EnemyBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "Components/SceneComponent.h"
#include "gp4_team_01/Public/APlayerCharacterController.h"
#include "AC_PetrifyGun.generated.h"

class UWorld;
class AEnemyBase;
class UClass;
class USceneComponent;
class AAPlayerCharacterController;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GP4_TEAM_01_API UAC_PetrifyGun : public UActorComponent
{
	GENERATED_BODY()
//methods
public:	
	// Sets default values for this component's properties
	UAC_PetrifyGun();
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
	FVector MuzzleOffset;
	FVector MuzzlePosition;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun")
	float TimeSinceLastShot;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gun")
	float ShotCooldown = 5.f; //value hardcoded for testing but exposed in editor. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
	float TraceLength = 1000.f; //exposed for easy editing,
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform")
	USceneComponent* SceneComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Controller")
	AAPlayerCharacterController* Controller;
private:
protected:

		
};
