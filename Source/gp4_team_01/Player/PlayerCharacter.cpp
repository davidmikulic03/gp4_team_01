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
#include "Engine.h"
#include "DSP/Osc.h"
#include "gp4_team_01/Player/MagnetComponent.h"


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
	CrouchAlpha = 12.f;
	PetrifyGunStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Petrify Gun StaticMesh");
	MagnetStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Magnet StaticMesh");
	ThrowableStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Throwable Mesh");
	SmokeBombStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Smoke Bomb Mesh");
	ThrowerComponent = CreateDefaultSubobject<UThrowerComponent>(TEXT("Thrower"));
	ThrowerComponent->SetupAttachment(Camera);
	PetrifyGun = CreateDefaultSubobject<UPetrifyGunComponent>(TEXT("Petrify Gun"));
	AIStimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AIStimuliComponent"));
	CurrentMoveIncrement = MinMoveIncriment;
	ThrowableInventory = CreateDefaultSubobject<UThrowableInventory>(TEXT("ThrowableInventory"));
	Magnet = CreateDefaultSubobject<UMagnetComponent>("Magnet");
	/*CustomCameraShake = CreateDefaultSubobject<UCameraShake>("Custom Camera Shake Component");*/
	OnActorBeginOverlap.AddDynamic(Magnet, &UMagnetComponent::BeginOverlap);
	OnActorEndOverlap.AddDynamic(Magnet, &UMagnetComponent::EndOverlap);
	PetrifyGunStaticMesh->SetupAttachment(Camera);
	MagnetStaticMesh->SetupAttachment(Camera);
	DetectionModifierComponent = CreateDefaultSubobject<UDetectionModifier>(TEXT("Detection Modifier Comp"));
	PetrifyGun->SetupAttachment(PetrifyGunStaticMesh);

	ThrowableStaticMesh->SetupAttachment(MagnetStaticMesh);
	SmokeBombStaticMesh->SetupAttachment(MagnetStaticMesh);
	ThrowableStaticMesh->SetVisibility(false);
	SmokeBombStaticMesh->SetVisibility(false);
}

void APlayerCharacter::Die() {
	if(auto GameMode = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(GetWorld()))) {
		//TODO: Put a bunch of stuff that happens when you die here, and probably delay the actually LoseGame call.
		OnDeath();
		GameMode->LoseGame();
	}
}

bool APlayerCharacter::InputIsPressed(FVector2D Value)
{
	float Epsilon = 0.00001f;
	if(Value.GetAbs().X >= Epsilon || Value.GetAbs().Y >= Epsilon)
	{
		UE_LOG(LogTemp, Warning, TEXT("Bro is shaking."));
		return true;
	}
	UE_LOG(LogTemp, Warning, TEXT("Bro is not shakind."));
	return false;
}

void APlayerCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	GenerateNoise(LandingNoiseDataAsset, GetActorLocation());
	UE_LOG(LogTemp, Warning, TEXT("Landed and made noise"));
}

void APlayerCharacter::TryGenerateNoise()
{
	if(GetMovementComponent()->IsCrouching()) {
		if(CrouchedNoiseDataAsset != nullptr) {
			GenerateNoise(CrouchedNoiseDataAsset, GetActorLocation());
		}
	}
	else {
		if(WalkingNoiseDataAsset != nullptr) {
			GenerateNoise(WalkingNoiseDataAsset, GetActorLocation());
		}
	}
}

void APlayerCharacter::GenerateNoise(UNoiseDataAsset* NoiseDataAsset, FVector Location)
{
	NoiseSystem->RegisterNoiseEvent(NoiseDataAsset, Location);
	UE_LOG(LogTemp, Warning, TEXT("Generating Noise"));
}

void APlayerCharacter::ActivateGun()
{
	bHasGun = true;
	PetrifyGunStaticMesh->SetVisibility(true);
}

void APlayerCharacter::DeactivateGun()
{
	bHasGun = false;
	PetrifyGunStaticMesh->SetVisibility(false);
}

void APlayerCharacter::ActivateMagnet()
{
	bHasMagnet = true;
	MagnetStaticMesh->SetVisibility(true);
}

void APlayerCharacter::DeactivateMagnet()
{
	bHasMagnet = false;
	MagnetStaticMesh->SetVisibility(false);
}

void APlayerCharacter::SaveRockCount()
{
	SavedThrowablesCount = ThrowableInventory->CurrentThrowables;
}

void APlayerCharacter::SaveGrenadeCount()
{
	SavedSmokeBombCount = ThrowableInventory->CurrentSmokeBombs;
}

void APlayerCharacter::LoadRockCount()
{
	ThrowableInventory->CurrentThrowables = SavedThrowablesCount;
}

void APlayerCharacter::LoadGrenadeCount()
{
	ThrowableInventory->CurrentSmokeBombs = SavedSmokeBombCount;
}

bool APlayerCharacter::TraceInteract(FHitResult& HitResult) {
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	
	FRotator StartRotation;
	FVector StartLocation;

	GetController()->GetPlayerViewPoint(StartLocation, StartRotation);
	FVector EndLocation = StartLocation + StartRotation.Vector() * 210.f;

	return GetWorld()->LineTraceSingleByChannel
	(
		HitResult,
		StartLocation,
		EndLocation,
		ECC_Visibility,
		QueryParams
	);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if(!bIncrementedMovement)
	{
		GetCharacterMovement()->MaxWalkSpeed = MoveSpeedWalk;
		GetCharacterMovement()->MaxWalkSpeedCrouched = MoveSpeedCrouch;
	}
	ThrowableInventory->AddPlayerRef(this);
	NoiseSystem = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->GetNoiseSystemRef();
	OriginalCameraPosition = Camera->GetRelativeLocation();
	bHasGun = false;
	bHasMagnet = false;
	//crouches
	bIsCrouching = true;
	//bHasGun and bHasMagnet are set to true on the first frame because DeactivateGunMesh and DeactivateMagnetMesh set them to the opposite of the value and then check
	bHasGun = true;
	bHasMagnet = true;
	GetCharacterMovement()->bWantsToCrouch = true;
	GetCharacterMovement()->Crouch();

	EquippedItem = ItemType::None;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DeltaValue += DeltaTime;
	float CrouchInterpolateTime = FMath::Min(1.f, CrouchAlpha * DeltaTime);
	EyeOffset = (1.0f - CrouchInterpolateTime) * EyeOffset;
	
	if(GetMovementComponent()->IsMovingOnGround() && GetMovementComponent()->Velocity.Length() > 0.2f) //TODO: remove magic numbers 
	{
		float temp = StepCounter;
		StepCounter += DeltaTime * MakeNoiseFrequency;
		if(FMath::Floor(temp) < FMath::Floor(StepCounter)) {
			TryGenerateNoise();
		}
	}
	if(FMath::IsNearlyZero((GetCharacterMovement()->Velocity.Length())) && Camera->GetRelativeLocation() != OriginalCameraPosition)
	{
		ResetCameraPosition();
	}
	// For displaying ui stuff.
	FHitResult Hit;
	TraceInteract(Hit);
	auto a = Cast<AInteractable>(Hit.GetActor());
	bool bNewValue = a != nullptr;
	if(bNewValue && !bCanInteract)
		OnCanInteract(a);
	else if(!bNewValue && bCanInteract)
		OnCannotInteract(a);
	bCanInteract = bNewValue;
	if(a != CurrentlyInteractableActor) {
		if(CurrentlyInteractableActor)
			CurrentlyInteractableActor->OnNotInteractable();
		if(a) {
			a->OnInteractable();
		}
	}
	CurrentlyInteractableActor = a;
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		/*EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveForward);
		EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MoveRight);*/
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		//crouch
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Crouch);
		EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Throw);
		EnhancedInputComponent->BindAction(PetrifyGunAction, ETriggerEvent::Triggered, this, &APlayerCharacter::FirePetrifyGun);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Jump);
		EnhancedInputComponent->BindAction(IncrementSpeedAction, ETriggerEvent::Triggered, this, &APlayerCharacter::IncrementMovement);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Interact);
		EnhancedInputComponent->BindAction(AimThrowableAction, ETriggerEvent::Triggered, this, &APlayerCharacter::AimThrowable);
		EnhancedInputComponent->BindAction(AimSmokeBombAction, ETriggerEvent::Triggered, this, &APlayerCharacter::AimSmokeBomb);
		EnhancedInputComponent->BindAction(AimThrowableAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopPredictingTrajectory);
		EnhancedInputComponent->BindAction(AimSmokeBombAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopPredictingTrajectory);
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Completed, this, &APlayerCharacter::OnPause);
	}
}

UThrowableInventory* APlayerCharacter::GetThrowableInventory()
{
	return ThrowableInventory;
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	if(Magnet->IsTraversing())
		return;
	const FVector2D InputVector = Value.Get<FVector2D>();

	if(Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), InputVector.Y);
		AddMovementInput((GetActorRightVector()), InputVector.X);
		CameraShake();
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
		ResetCameraPosition();
		UE_LOG(LogTemp, Warning, TEXT("Crouched"));
	}
	else if(!bIsCrouching)
	{
		GetCharacterMovement()->bWantsToCrouch = false;
		GetCharacterMovement()->UnCrouch();
		ResetCameraPosition();
		UE_LOG(LogTemp, Warning, TEXT("Stood up"));
	}
}

void APlayerCharacter::Throw(const FInputActionValue& Value)
{
	if(ThrowableInventory->GetCurrentCount(EquippedItem) > 0 && !ThrowerComponent->IsOnCooldown())
	{
		ThrowerComponent->Launch(EquippedItem);
		ThrowableInventory->RemoveItem(EquippedItem);
		ThrowerComponent->ResetCooldown();

		if(ThrowableInventory->GetCurrentCount(EquippedItem) == 0)
			StopPredictingTrajectory(Value);
	}
	else if(ThrowerComponent->IsOnCooldown())
	{
		UE_LOG(LogTemp, Warning, TEXT("On Cooldown."));		
	}
	else if(ThrowableInventory->GetCurrentCount(EquippedItem) <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't throw. Nothing in the inventory."));	
	}
}

void APlayerCharacter::FirePetrifyGun(const FInputActionValue& Value)
{
	if(bHasGun && !Magnet->IsTraversing())
	{
		PetrifyGun->TryFirePetrifyGun();
	}

}

void APlayerCharacter::IncrementMovement(const FInputActionValue& Value)
{
	if(bIncrementedMovement)
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
	bool bHit = TraceInteract(HitResult); 

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
	//DrawDebugLine(GetWorld(),StartLocation, EndLocation, FColor::Red, false, 3.f, 3.f);
}

void APlayerCharacter::AimThrowable(const FInputActionValue& Value) {
	if(ThrowableInventory->GetCurrentCount(ItemType::Throwable) > 0) {
		PredictTrajectory(Value, ItemType::Throwable);
		DeactivateMagnet();
		
		if(!ThrowerComponent->IsOnCooldown())
			ThrowableStaticMesh->SetVisibility(true);
		else
			ThrowableStaticMesh->SetVisibility(false);
		
		EquippedItem = ItemType::Throwable;
	}
}

void APlayerCharacter::AimSmokeBomb(const FInputActionValue& Value) {
	if(ThrowableInventory->GetCurrentCount(ItemType::SmokeBomb) > 0) {
		PredictTrajectory(Value, ItemType::SmokeBomb);
		DeactivateMagnet();
		
		if(!ThrowerComponent->IsOnCooldown())
			SmokeBombStaticMesh->SetVisibility(true);
		else
			SmokeBombStaticMesh->SetVisibility(false);
		
		EquippedItem = ItemType::SmokeBomb;
	}
}

void APlayerCharacter::OnPause() {
	if(AMainGameMode* const GameMode = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
		GameMode->PauseGame();
}

void APlayerCharacter::PredictTrajectory(const FInputActionValue& Value, ItemType ItemType)
{
	FPredictProjectilePathResult Result = ThrowerComponent->PredictTrajectory();
	ThrowerComponent->DrawProjectilePath(Result, ItemType);
}

void APlayerCharacter::StopPredictingTrajectory(const FInputActionValue& Value) {
	ThrowerComponent->HideProjectilePath();

	SmokeBombStaticMesh->SetVisibility(false);
	ThrowableStaticMesh->SetVisibility(false);
	ActivateMagnet();
	
	EquippedItem = ItemType::None;
}

void APlayerCharacter::CameraShake()
{
	float NormalizedWalkTimeZ = StepCounter;
	float NormalizedWalkTimeY = StepCounter / 2;
	
	if(!bIsCrouching)
	{
		float DeltaZ = AmplitudeWalking * FMath::Sin(NormalizedWalkTimeZ * TWO_PI);
		float DeltaY = AmplitudeWalking * FMath::Sin(NormalizedWalkTimeY * TWO_PI) * AmplitudeFractionWalking;
		Camera->AddLocalOffset(FVector(0.f, DeltaY, DeltaZ));
	}
	else if(bIsCrouching)
	{
		float DeltaZ = AmplitudeCrouching * FMath::Sin(NormalizedWalkTimeZ * TWO_PI); //add fraction
		float DeltaY = AmplitudeWalking * FMath::Sin(NormalizedWalkTimeY * TWO_PI) * AmplitudeFractionCrouched;
		Camera->AddLocalOffset(FVector(0.f, DeltaY, DeltaZ));
	}
}

void APlayerCharacter::ResetCameraPosition()
{
	FVector NewCameraPosition = FMath::Lerp(Camera->GetRelativeLocation(), OriginalCameraPosition, CameraResetLerpTime);
	Camera->SetRelativeLocation(NewCameraPosition);
	UE_LOG(LogTemp, Warning, TEXT("Returned the camera to start location"));
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
	DetectionModifierComponent->SetDetectionSignalModifier(0.1f); //magic number - expose as a UPROPERTY;
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
	DetectionModifierComponent->SetDetectionSignalModifier(1.f);
}

void APlayerCharacter::CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult)
{
	if (Camera != nullptr)
	{
		Camera->GetCameraView(DeltaTime, OutResult);
		OutResult.Location += EyeOffset;
	}
}


