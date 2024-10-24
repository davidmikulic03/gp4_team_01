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
#include "gp4_team_01/DataAssets/NoiseDataAsset.h"
#include "gp4_team_01/Enviroment/NoiseMaker.h"
#include "gp4_team_01/Systems/NoiseSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "ThrowableInventory.h"
#include "CameraShake.h"
#include "gp4_team_01/Enemies/AI/DetectionModifier.h"
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
class ANoiseSystem;
class UCameraShake;
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
	UFUNCTION(BlueprintImplementableEvent)
	void OnStartMagnetTraversal();
	UFUNCTION(BlueprintImplementableEvent)
	void OnFinishMagnetTraversal();
	UFUNCTION(BlueprintImplementableEvent)
	void OnDeath();
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnCanInteract(AInteractable* Actor);
	UFUNCTION(BlueprintImplementableEvent)
	void OnCannotInteract(AInteractable* Actor);

	UFUNCTION(BlueprintCallable)
		void Die();


	UFUNCTION()
	bool InputIsPressed(FVector2D Value);
	
	void Landed(const FHitResult& Hit) override;
	//noise calculations
	UFUNCTION()
	void TryGenerateNoise();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	void Move(const FInputActionValue& Value);
	/*void MoveForward(const FInputActionValue& Value);
	void MoveRight(const FInputActionValue& Value);*/
	void Look(const FInputActionValue& Value);
	void Crouch(const FInputActionValue& Value);
	void Throw(const FInputActionValue& Value);
	void FirePetrifyGun(const FInputActionValue& Value);
	void IncrementMovement(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	void Interact(const FInputActionValue& Value);
	void AimThrowable(const FInputActionValue& Value);
	void AimSmokeBomb(const FInputActionValue& Value);

	void OnPause();
	
	void StopPredictingTrajectory(const FInputActionValue& Value);

	void PredictTrajectory(const FInputActionValue& Value, ItemType ItemType);
	//variables and methods

	void CameraShake();
	void ResetCameraPosition();
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
	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveForwardAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveRightAction;*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* CrouchAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ThrowAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PetrifyGunAction;	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IncrementSpeedAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AimThrowableAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AimSmokeBombAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PauseAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Static Mesh")
	UStaticMeshComponent* PetrifyGunStaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Static Mesh")
	UStaticMeshComponent* MagnetStaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Static Mesh")
	UStaticMeshComponent* ThrowableStaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Static Mesh")
	UStaticMeshComponent* SmokeBombStaticMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float CrouchAlpha;
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UDetectionModifier* DetectionModifierComponent;

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

	//noise
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement/Noise")
	float NoiseScaleMovement = 10.f; //noise generated as player is moving
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement/Noise")
	float MovementSpeedFraction = 0.1f; //used to calculate NoiseScale when moving slower or faster
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement/Noise")
	float CrouchedFraction = 0.5f; //added to the calculation when crouched
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement/Noise")
	float StepCounter = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement/Noise")
	float MakeNoiseFrequency = .75f; //test value. Edit later in the Blueprint.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement/Noise")
	UNoiseDataAsset* CrouchedNoiseDataAsset;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement/Noise")
	UNoiseDataAsset* WalkingNoiseDataAsset;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement/Noise")
	UNoiseDataAsset* LandingNoiseDataAsset;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement/Noise")
	ANoiseSystem* NoiseSystem;
	void GenerateNoise(UNoiseDataAsset* NoiseDataAsset, FVector Location);

	//camera shake
	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Shake")
	UCameraShake* CustomCameraShake; //*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera Shake")
	float AmplitudeWalking = 1.0f; //the amplitude of the SIN function. Recommended balue is 0.25 and the recommended range is 0 to 1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera Shake")
	float AmplitudeCrouching = .5f; //the amplitude of the SIN function whem crouched. Recommended value is half of walking.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera Shake")
	float AmplitudeFractionWalking = 1.0f; //the amount that the final result is divided by;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera Shake")
	float AmplitudeFractionCrouched = .5f; //the amount that the final result is divided by. Recommended amount is two times the size of the walking Fraction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera Shake")
	float ShakeSpeedWalking = 1.0f; //how fast the camera moves up and down
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera Shake")
	float ShakeSpeedCrouched = .5f; //how fast the camera moves up and down. Recommended value is one half of what ShakeSpeedWalking is
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Shake")
	float CameraResetLerpTime = 0.5f; //keep this in 0 to 1 range.
	float DeltaValue;
	FVector OriginalCameraPosition;

	//deactivate meshes variables and functions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	bool bHasGun;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	bool bHasMagnet;
	UFUNCTION(BlueprintCallable)
	void ActivateGun();
	UFUNCTION(BlueprintCallable)
	void DeactivateGun();
	UFUNCTION(BlueprintCallable)
	void ActivateMagnet();
	UFUNCTION(BlueprintCallable)
	void DeactivateMagnet();

	//inventory counters - for saving - is it persistent?
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Non-Modifiable")
	float SavedThrowablesCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Non-Modifiable")
	float SavedSmokeBombCount;

	UFUNCTION(BlueprintCallable)
		void SavePlayerState() { SaveRockCount(); SaveGrenadeCount(); }
	UFUNCTION(BlueprintCallable)
		void LoadPlayerState()
	{
		LoadRockCount();
		LoadGrenadeCount();
		Crouch(FInputActionValue());
	}
	UFUNCTION()
	void SaveRockCount();
	UFUNCTION()
	void SaveGrenadeCount();
	UFUNCTION()
	void LoadRockCount();
	UFUNCTION()
	void LoadGrenadeCount();
	UFUNCTION(BlueprintCallable)
	bool GetCameraShakeOn();
	UFUNCTION(BlueprintCallable)
	void SetCameraShakeOn(bool Value);
protected:
	bool TraceInteract(FHitResult& HitResult);
	bool bCanInteract = false;

	ItemType EquippedItem = ItemType::None;

	AInteractable* CurrentlyInteractableActor = nullptr;
private:
	bool bCameraShakeOn = true;
};
