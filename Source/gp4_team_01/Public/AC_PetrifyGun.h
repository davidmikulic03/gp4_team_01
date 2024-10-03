// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "AC_PetrifyGun.generated.h"

class UWorld;

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun")
	float TimeSinceLastShot;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gun")
	float ShotCooldown = 5.f; //value hardcoded for testing but exposed in editor. 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
	float TraceLength = 1000.f; //exposed for easy editing,
private:
protected:

		
};
