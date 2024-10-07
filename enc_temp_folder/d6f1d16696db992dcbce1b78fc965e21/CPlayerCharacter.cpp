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
	AIStimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AIStimuliComponent"));
	CurrentMoveIncrement = MinMoveIncriment;
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
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::Jump);
		EnhancedInputComponent->BindAction(IncrementSpeedAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::IncrementMovement);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::Interact);
	}

}

void ACPlayerCharacter::MoveForward(const FInputActionValue& Value)
{
	FVector2D InputVector = Value.Get<FVector2D>();
	//redo increment movement
	if(Controller != nullptr)
	{
		if(bIncrementedMovement)
		{
			switch(CurrentMoveIncrement)
			{
			case 1:
				CurrentMoveIncrement = MinMoveIncriment;
				GetCharacterMovement()->MaxWalkSpeed = MoveIncrementSpeed * CurrentMoveIncrement;
				GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchIncrementSpeed * CurrentMoveIncrement;
				break;
			case 2:
				CurrentMoveIncrement = 2;
				GetCharacterMovement()->MaxWalkSpeed = MoveIncrementSpeed * CurrentMoveIncrement;
				GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchIncrementSpeed * CurrentMoveIncrement;
				break;
			case 3:
				CurrentMoveIncrement = 3;
				GetCharacterMovement()->MaxWalkSpeed = MoveIncrementSpeed * CurrentMoveIncrement;
				GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchIncrementSpeed * CurrentMoveIncrement;
				break;
			case 4:
				CurrentMoveIncrement = 4;
				GetCharacterMovement()->MaxWalkSpeed = MoveIncrementSpeed * CurrentMoveIncrement;
				GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchIncrementSpeed * CurrentMoveIncrement;
				break;
			case 5:
				CurrentMoveIncrement = 5;
				GetCharacterMovement()->MaxWalkSpeed = MoveIncrementSpeed * CurrentMoveIncrement;
				GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchIncrementSpeed * CurrentMoveIncrement;
				break;
			case 6:
				CurrentMoveIncrement = MaxMoveIncrement;
				GetCharacterMovement()->MaxWalkSpeed = MoveIncrementSpeed * CurrentMoveIncrement;
				GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchIncrementSpeed * CurrentMoveIncrement;
				break;
			}
			AddMovementInput(GetActorForwardVector(), InputVector.X);

		}
		else if(!bIncrementedMovement)
		{
			AddMovementInput(GetActorForwardVector(), InputVector.X);
		}
	}
}

void ACPlayerCharacter::MoveRight(const FInputActionValue& Value)
{
	//redo increment movement
	FVector2D InputVector = Value.Get<FVector2D>();
	if(Controller != nullptr)
	{
		if (bIncrementedMovement)
		{
			switch (CurrentMoveIncrement)
			{
			case 1:
				CurrentMoveIncrement = MinMoveIncriment;
				GetCharacterMovement()->MaxWalkSpeed = MoveIncrementSpeed * CurrentMoveIncrement;
				GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchIncrementSpeed * CurrentMoveIncrement;
				break;
			case 2:
				CurrentMoveIncrement = 2;
				GetCharacterMovement()->MaxWalkSpeed = MoveIncrementSpeed * CurrentMoveIncrement;
				GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchIncrementSpeed * CurrentMoveIncrement;
				break;
			case 3:
				CurrentMoveIncrement = 3;
				GetCharacterMovement()->MaxWalkSpeed = MoveIncrementSpeed * CurrentMoveIncrement;
				GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchIncrementSpeed * CurrentMoveIncrement;
				break;
			case 4:
				CurrentMoveIncrement = 4;
				GetCharacterMovement()->MaxWalkSpeed = MoveIncrementSpeed * CurrentMoveIncrement;
				GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchIncrementSpeed * CurrentMoveIncrement;
				break;
			case 5:
				CurrentMoveIncrement = 5;
				GetCharacterMovement()->MaxWalkSpeed = MoveIncrementSpeed * CurrentMoveIncrement;
				GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchIncrementSpeed * CurrentMoveIncrement;
				break;
			case 6:
				CurrentMoveIncrement = MaxMoveIncrement;
				GetCharacterMovement()->MaxWalkSpeed = MoveIncrementSpeed * CurrentMoveIncrement;
				GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchIncrementSpeed * CurrentMoveIncrement;
				break;
			}
			AddMovementInput(GetActorRightVector(), InputVector.X);

		}
		else if (!bIncrementedMovement)
		{
			GetCharacterMovement()->MaxWalkSpeed = MoveSpeedWalk;
			GetCharacterMovement()->MaxWalkSpeedCrouched = MoveSpeedCrouch;
			AddMovementInput(GetActorRightVector(), InputVector.X);
		}
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
}

void ACPlayerCharacter::Throw(const FInputActionValue& Value)
{
	ThrowerComponent->Launch();
}

void ACPlayerCharacter::FirePetrifyGun(const FInputActionValue& Value)
{
	PetrifyGun->TryFirePetrifyGun();
}

void ACPlayerCharacter::IncrementMovement(const FInputActionValue& Value)
{
	FVector2D InputVector = Value.Get<FVector2D>();

	if(InputVector.X < 0)
	{
		CurrentMoveIncrement--;
		if (CurrentMoveIncrement <= MinMoveIncriment)
		{
			CurrentMoveIncrement = MinMoveIncriment;
		}
	}
	else if(InputVector.X > 0)
	{
		CurrentMoveIncrement++;
		if(CurrentMoveIncrement >= MaxMoveIncrement)
		{
			CurrentMoveIncrement = MaxMoveIncrement;
		}
	}
}

void ACPlayerCharacter::Jump(const FInputActionValue& Value)
{
	Super::Jump();
}

void ACPlayerCharacter::Interact(const FInputActionValue& Value)
{
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);


	FRotator StartRotation;
	FVector StartLocation;

	GetController()->GetPlayerViewPoint(StartLocation, StartRotation);
	FVector EndLocation = StartLocation + StartRotation.Vector() * 500.f;

	bool bHit = GetWorld()->LineTraceSingleByChannel
	(
		HitResult,
		StartLocation,
		EndLocation,
		ECC_Visibility,
		QueryParams
	);

	if(bHit)
	{
		AInteractable* HitActor = Cast<AInteractable>(HitResult.GetActor());
		if(HitActor)
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit actor with interface"));
			
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit nothing"));
		}
		
	}
	DrawDebugLine(GetWorld(),StartLocation, EndLocation, FColor::Red, false, 3.f, 3.f);
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
