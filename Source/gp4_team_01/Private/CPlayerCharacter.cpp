// Fill out your copyright notice in the Description page of Project Settings.

#include "CPlayerCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "Delegates/DelegateSignatureImpl.inl"

// Sets default values
ACPlayerCharacter::ACPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;	
	GetCapsuleComponent()->SetSimulatePhysics(false);
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.f);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->SetRelativeLocation(FVector(-10.f, 0.f, 60.f));
	Camera->bUsePawnControlRotation = true;
	EyeOffset = FVector(0.f);
	AlphaValue = 12.f;
	ThrowerComponent = CreateDefaultSubobject<UAC_ThrowerComponent>(TEXT("Thrower"));
	PetrifyGun = CreateDefaultSubobject<UAC_PetrifyGun>(TEXT("Petrify Gun"));
}

// Called when the game starts or when spawned
void ACPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeedWalk;
	GetCharacterMovement()->MaxWalkSpeedCrouched = MoveSpeedCrouch;
}



// Called every frame
void ACPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float CrouchInterpolateTime = FMath::Min(1.f, AlphaValue * DeltaTime);
	EyeOffset = (1.0f - CrouchInterpolateTime) * EyeOffset;

}

// Called to bind functionality to input
void ACPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::MoveForward);
		EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::MoveRight);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::Look);
		//crouch
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::Crouch);
		EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::Throw);
		EnhancedInputComponent->BindAction(PetrifyGunAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::FirePetrifyGun);

	}

}

void ACPlayerCharacter::MoveForward(const FInputActionValue& Value)
{
	FVector2D InputVector = Value.Get<FVector2D>();
	if(Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), InputVector.X);
	}
}

void ACPlayerCharacter::MoveRight(const FInputActionValue& Value)
{
	FVector2D InputVector = Value.Get<FVector2D>();
	if(Controller != nullptr)
	{
		AddMovementInput(GetActorRightVector(), InputVector.X);
	}
}

void ACPlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D InputVector = Value.Get<FVector2D>();
	if(Controller != nullptr)
	{
		AddControllerYawInput(InputVector.X);
		AddControllerPitchInput(-InputVector.Y);
	}

}

void ACPlayerCharacter::Crouch(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Trying to Crouch"));
	bIsCrouching = !bIsCrouching;

	if(bIsCrouching)
	{
		GetCharacterMovement()->bWantsToCrouch = true;
		GetCharacterMovement()->Crouch();
		UE_LOG(LogTemp, Warning, TEXT("Crouched"));
	}
	else if(!bIsCrouching)
	{
		GetCharacterMovement()->bWantsToCrouch = false;
		GetCharacterMovement()->UnCrouch();
		UE_LOG(LogTemp, Warning, TEXT("Stood up"));
	}
	//this is the way I would do it in Unity - however it's only in the update method and it triggers multiple times. I need to find out why.
}

void ACPlayerCharacter::Throw(const FInputActionValue& Value)
{
	ThrowerComponent->Launch();
}

void ACPlayerCharacter::FirePetrifyGun(const FInputActionValue& Value)
{
	PetrifyGun->TryFirePetrifyGun();
}

void ACPlayerCharacter::OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	if(HalfHeightAdjust == 0.f)
	{
		return;
	}

	float StartBaseEyeHeight = BaseEyeHeight;
	Super::OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	EyeOffset.Z += StartBaseEyeHeight - BaseEyeHeight + HalfHeightAdjust;
	Camera->SetRelativeLocation(FVector(0.f, 0.f, BaseEyeHeight), false);
}

void ACPlayerCharacter::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	if (HalfHeightAdjust == 0.f)
	{
		return;
	}
	float StartBaseEyeHeight = BaseEyeHeight;
	Super::OnEndCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	EyeOffset.Z += StartBaseEyeHeight - BaseEyeHeight - HalfHeightAdjust;
	Camera->SetRelativeLocation(FVector(0.f, 0.f, BaseEyeHeight), false);
}

void ACPlayerCharacter::CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult)
{
	if (Camera != nullptr)
	{
		Camera->GetCameraView(DeltaTime, OutResult);
		OutResult.Location += EyeOffset;

	}
}
