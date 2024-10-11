// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "Delegates/DelegateSignatureImpl.inl"
#include "gp4_team_01/Player/MagnetComponent.h"
#include "Kismet/GameplayStaticsTypes.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
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
	ThrowerComponent = CreateDefaultSubobject<UThrowerComponent>(TEXT("Thrower"));
	ThrowerComponent->SetupAttachment(Camera);
	PetrifyGun = CreateDefaultSubobject<UPetrifyGunComponent>(TEXT("Petrify Gun"));
	AIStimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AIStimuliComponent"));
	CurrentMoveIncrement = MinMoveIncriment;
	ThrowableInventory = CreateDefaultSubobject<UThrowableInventory>(TEXT("ThrowableInventory"));
	Magnet = CreateDefaultSubobject<UMagnetComponent>("Magnet");
	OnActorBeginOverlap.AddDynamic(Magnet, &UMagnetComponent::BeginOverlap);
	OnActorEndOverlap.AddDynamic(Magnet, &UMagnetComponent::EndOverlap);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = MoveSpeedWalk;
	GetCharacterMovement()->MaxWalkSpeedCrouched = MoveSpeedCrouch;

	ThrowableInventory->AddPlayerRef(this);
}



// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float CrouchInterpolateTime = FMath::Min(1.f, AlphaValue * DeltaTime);
	EyeOffset = (1.0f - CrouchInterpolateTime) * EyeOffset;

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveForward);
		EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveRight);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		//crouch
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Crouch);
		EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Throw);
		EnhancedInputComponent->BindAction(PetrifyGunAction, ETriggerEvent::Triggered, this, &APlayerCharacter::FirePetrifyGun);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Jump);
		EnhancedInputComponent->BindAction(IncrementSpeedAction, ETriggerEvent::Triggered, this, &APlayerCharacter::IncrementMovement);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Interact);
		EnhancedInputComponent->BindAction(PredictTrajectoryAction, ETriggerEvent::Triggered, this, &APlayerCharacter::PredictTrajectory);
	}

}

UThrowableInventory* APlayerCharacter::GetThrowableInventory()
{
	return ThrowableInventory;
}

void APlayerCharacter::MoveForward(const FInputActionValue& Value)
{
	if(Magnet->IsTraversing())
		return;
	FVector2D InputVector = Value.Get<FVector2D>();
	//redo increment movement
	if(Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), InputVector.X);
	}
}

void APlayerCharacter::MoveRight(const FInputActionValue& Value)
{
	if(Magnet->IsTraversing())
		return;
	//redo increment movement
	FVector2D InputVector = Value.Get<FVector2D>();
	if(Controller != nullptr)
	{
		AddMovementInput(GetActorRightVector(), InputVector.X);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D InputVector = Value.Get<FVector2D>();
	if(Controller != nullptr)
	{
		AddControllerYawInput(InputVector.X);
		AddControllerPitchInput(-InputVector.Y);
	}

}

void APlayerCharacter::Crouch(const FInputActionValue& Value)
{
	if(Magnet->IsTraversing())
		return;
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

void APlayerCharacter::Throw(const FInputActionValue& Value)
{
	if(ThrowableInventory->GetCurrentCount(ItemType::Throwable) > 0 && !ThrowerComponent->IsOnCooldown())
	{
		ThrowerComponent->Launch();
		ThrowableInventory->RemoveItem(ItemType::Throwable);
		ThrowerComponent->ResetCooldown();
	}
	else if(ThrowerComponent->IsOnCooldown())
	{
		UE_LOG(LogTemp, Warning, TEXT("On Cooldown."));		
	}
	else if(ThrowableInventory->GetCurrentCount(ItemType::Throwable) <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't throw. Nothing in the inventory."));	
	}
}

void APlayerCharacter::FirePetrifyGun(const FInputActionValue& Value)
{
	PetrifyGun->TryFirePetrifyGun();
}

void APlayerCharacter::IncrementMovement(const FInputActionValue& Value)
{
	FVector2D InputVector = Value.Get<FVector2D>();
	if(InputVector.X < 0)
	{
		CurrentMoveIncrement--;
		if (CurrentMoveIncrement <= MinMoveIncriment)
		{
			CurrentMoveIncrement = MinMoveIncriment;
		}
		GetCharacterMovement()->MaxWalkSpeed = MoveIncrementSpeed * CurrentMoveIncrement;
		GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchIncrementSpeed * CurrentMoveIncrement;
	}
	else if(InputVector.X > 0)
	{
		CurrentMoveIncrement++;
		if(CurrentMoveIncrement >= MaxMoveIncrement)
		{
			CurrentMoveIncrement = MaxMoveIncrement;
		}
		GetCharacterMovement()->MaxWalkSpeed = MoveIncrementSpeed * CurrentMoveIncrement;
		GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchIncrementSpeed * CurrentMoveIncrement;
	}
}

void APlayerCharacter::Jump(const FInputActionValue& Value)
{
	if(Magnet->IsTraversing())
		return;
	Super::Jump();
}

void APlayerCharacter::Interact(const FInputActionValue& Value)
{
	if(Magnet->IsTraversing() || Magnet->Use())
		return;
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
			HitActor->Interact(this);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit nothing"));
		}
		
	}
	DrawDebugLine(GetWorld(),StartLocation, EndLocation, FColor::Red, false, 3.f, 3.f);
}

void APlayerCharacter::PredictTrajectory(const FInputActionValue& Value)
{
	FPredictProjectilePathResult Result = ThrowerComponent->PredictTrajectory();
	ThrowerComponent->DrawProjectilePath(Result);
}



void APlayerCharacter::OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
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

void APlayerCharacter::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
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

void APlayerCharacter::CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult)
{
	if (Camera != nullptr)
	{
		Camera->GetCameraView(DeltaTime, OutResult);
		OutResult.Location += EyeOffset;

	}
}
