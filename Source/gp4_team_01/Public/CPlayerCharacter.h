// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "AC_ThrowerComponent.h"
#include "AC_PetrifyGun.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Hearing.h"
#include "CPlayerCharacter.generated.h"

class UInputComponent;
class UCapsuleComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class UCharacterMovementComponent;
class UAC_ThrowerComponent;
class UAC_PetrifyGun;
class UAIPerceptionStimuliSourceComponent;
struct FInputActionValue;

UCLASS()
class GP4_TEAM_01_API ACPlayerCharacter : public ACharacter
{
	GENERATED_BODY()
	//method
public:
	// Sets default values for this character's properties
	ACPlayerCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	void CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult) override;

	//void Fire(const FInputActionValue& Value);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:	
	void MoveForward(const FInputActionValue& Value);
	void MoveRight(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Crouch(const FInputActionValue& Value);
	void Throw(const FInputActionValue& Value);
	void FirePetrifyGun(const FInputActionValue& Value);
	void IncrementMovement(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	//variables and methods
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveSpeedWalk = 300.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Movement")
	float MoveSpeedCrouch = 150.f;
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	bool bIsCrouching = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;
public:
	//actions
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveForwardAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveRightAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* CrouchAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ThrowAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PetrifyGunAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float AlphaValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector EyeOffset;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UAC_ThrowerComponent* ThrowerComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UAC_PetrifyGun* PetrifyGun;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UAIPerceptionStimuliSourceComponent* AIStimuliSource;

	//experimental
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	int MaxMoveIncrements = 6;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	int MinMoveIncriments = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveIncrementSpeed = 60.f;
protected:
};
