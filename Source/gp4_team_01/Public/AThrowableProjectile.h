// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "AThrowableProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class GP4_TEAM_01_API AAThrowableProjectile : public AActor
{
	GENERATED_BODY()
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* CollisionComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

	//methods
public:	
	AAThrowableProjectile();
	virtual void Tick(float DeltaTime) override;
	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
protected:
	virtual void BeginPlay() override;
private:	



	//variables and components
private:
protected: 
public:

};
