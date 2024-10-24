// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "gp4_team_01/DataAssets/NoiseDataAsset.h"
#include "gp4_team_01/Enviroment/NoiseMaker.h"
#include "gp4_team_01/Systems/NoiseSystem.h"
#include "gp4_team_01/Systems/MainGameMode.h"
#include "ThrowableProjectile.generated.h"

enum class ItemType : uint8;
class USphereComponent;
class UProjectileMovementComponent;
class ANoiseSystem;
class AMainGameMode;

UCLASS()
class GP4_TEAM_01_API AThrowableProjectile : public AActor, public INoiseMaker
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComp;
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	UProjectileMovementComponent* ProjectileMovement;

	//methods
public:
	AThrowableProjectile();
	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
	
	virtual void Tick(float DeltaTime) override;

	virtual void GenerateNoise(UNoiseDataAsset* NoiseDataAsset, FVector Location) override;	
protected:
	virtual void BeginPlay() override;


protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* ThrowableMesh = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UNoiseDataAsset* NoiseDataAsset;
	
private:
	//variables and components
	class ANoiseSystem* NoiseSystem;
private:

protected:

public:
};

