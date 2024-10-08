// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AThrowableProjectile.h"
#include "APlayerCharacterController.h"
#include "GameFramework/GameModeBase.h"
#include  "gp4_team_01/Public/ThrowableInventory.h"
#include "AC_ThrowerComponent.generated.h"

class AAThrowableProjectile;
class UObject;
class ACPlayerCharacter;
class AAPlayerCharacterController;
class UThrowableInventory;
class UWorld;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GP4_TEAM_01_API UAC_ThrowerComponent : public UActorComponent
{
	GENERATED_BODY()
	//methods
public:	
	UAC_ThrowerComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION()
	void Launch();
	UFUNCTION()
	void ResetCooldown();
	UFUNCTION()
	bool IsOnCooldown();
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
private:
	TObjectPtr<ACPlayerCharacter> PlayerCharacter;
	UPROPERTY(EditDefaultsOnly, Category = "Thrower")
	TSubclassOf<AAThrowableProjectile> Throwable;
	UPROPERTY(EditAnywhere, Category = "Thrower")
	FVector MuzzleOffset;
	AGameModeBase* GameMode;
	UPROPERTY(EditAnywhere, Category = "Thrower")
	float ThrowAngle = 30.f;
};
