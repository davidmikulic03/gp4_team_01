// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Camera/CameraComponent.h"
#include "CameraShake.generated.h"

class UCameraComponent;
class UWorld;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GP4_TEAM_01_API UCameraShake : public UActorComponent
{
	GENERATED_BODY()

	//methods
public:
	UCameraShake();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION()
	void CameraShake(float InputValue);
	UCameraComponent* GetPlayerCamera();
	void DebugMessage();
protected:
	virtual void BeginPlay() override;
private:

	
	//variables
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Shake")
	bool bCameraShakeOn = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Shake")
	UCameraComponent* Camera;
	//Determines how violent the camera shakes are - 1.0f is a default.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera Shake")
	float ShakeIntensity = 1.0f;
	//Determines how quick the shakes are - having this value too low can cause motion sickness (?)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera Shake")
	float ShakeDuration = 0.25f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Shake")
	FVector OriginalCameraPosition;
	FRotator OriginalCameraRotation;
protected:
private:
	
};
