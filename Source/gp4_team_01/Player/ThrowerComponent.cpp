// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrowerComponent.h"

// Sets default values for this component's properties
UThrowerComponent::UThrowerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MuzzleOffset = FVector(300.f, 0.f, 10.f);
}


// Called when the game starts
void UThrowerComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UThrowerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TimeSinceLastThrown += DeltaTime;
}

void UThrowerComponent::Launch()
{
	if(GetWorld()->GetFirstPlayerController()->GetPawn() == nullptr || GetWorld()->GetFirstPlayerController() == nullptr)
	{
		return;
	}

	if(Throwable != nullptr && TimeSinceLastThrown >= ThrowCooldown)
	{
		UWorld* const World = GetWorld();
		if(World !=nullptr)
		{
			APlayerCharacterController* Controller = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());

			const FRotator SpawnRotation = Controller->PlayerCameraManager->GetCameraRotation() + FRotator(0.f, 0.f, ThrowAngle);
			const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);

			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			World->SpawnActor<AThrowableProjectile>(Throwable, SpawnLocation, SpawnRotation, SpawnParams);
			UE_LOG(LogTemp, Warning, TEXT("Throwable spawned and thrown"));
		}
	}
	else if(TimeSinceLastThrown <= ThrowCooldown)
	{
		UE_LOG(LogTemp, Warning, TEXT("Throw on cooldown"));		
	}
}

void UThrowerComponent::ResetCooldown()
{
	TimeSinceLastThrown = 0;
}

bool UThrowerComponent::IsOnCooldown()
{
	if(TimeSinceLastThrown >= ThrowCooldown)
	{
		return false;	
	}
	else if(TimeSinceLastThrown <= ThrowCooldown)
	{
		return true;
	}
	return false;
}

