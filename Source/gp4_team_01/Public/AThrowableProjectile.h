// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "AThrowableProjectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class GP4_TEAM_01_API AAThrowableProjectile : public AActor
{
	GENERATED_BODY()
	//methods
public:	
	AAThrowableProjectile();
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
private:	



	//variables and components
private:

protected: 

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UProjectileMovementComponent* ProjectileMovementComponent;
};
