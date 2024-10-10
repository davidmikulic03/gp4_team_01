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
#include "ThrowerComponent.h"
#include "PetrifyGunComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Hearing.h"
#include "gp4_team_01/Enviroment/Interactable.h"
#include "ThrowableInventory.h"
#include "PlayerCharacter.generated.h"

class UMagnetComponent;
class UInputComponent;
class UCapsuleComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class UCharacterMovementComponent;
class UThrowerComponent;
class UPetrifyGunComponent;
class UAIPerceptionStimuliSourceComponent;
class AInteractable;
class UThrowableInventory;
struct FInputActionValue;

UCLASS()
class GP4_TEAM_01_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()
	//method
public:
	// Sets default values for this character's properties
	APlayerCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE UCameraComponent* GetCamera() const noexcept { return Camera; }

	//getters
	UFUNCTION(BlueprintCallable)
	UThrowableInventory* GetThrowableInventory();

	void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	void CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult) override;

	//Inventory events for player HUD
	UFUNCTION(BlueprintImplementableEvent)
	void OnInventoryUpdated();

	UFUNCTION(BlueprintImplementableEvent)
	void OnMaxThrowables();

	UFUNCTION(BlueprintImplementableEvent)
	void OnMaxSmokeBombs();
	
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
	void Interact(const FInputActionValue& Value);
	//variables and methods
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveSpeedWalk = 300.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Movement")
	float MoveSpeedCrouch = 150.f;
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	bool bIsCrouching = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	UThrowableInventory* ThrowableInventory;
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IncrementSpeedAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float AlphaValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector EyeOffset;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UThrowerComponent* ThrowerComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UPetrifyGunComponent* PetrifyGun;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UAIPerceptionStimuliSourceComponent* AIStimuliSource;
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UMagnetComponent* Magnet;

	//experimental
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	int MaxMoveIncrement = 6;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	int MinMoveIncriment = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	int CurrentMoveIncrement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveIncrementSpeed = 60.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float CrouchIncrementSpeed = 30.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool bIncrementedMovement = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector CameraOffset; //this is the value for camera offset. It should be the same as the camera Offset.
	
protected:
	
};
