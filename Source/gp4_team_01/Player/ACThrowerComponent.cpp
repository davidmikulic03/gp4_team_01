// Fill out your copyright notice in the Description page of Project Settings.


#include "ACThrowerComponent.h"

#include "CPlayerCharacter.h"


// Sets default values for this component's properties
UACThrowerComponent::UACThrowerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MuzzleOffset = FVector(300.f, 0.f, 10.f);
	
}


// Called when the game starts
void UACThrowerComponent::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<ACPlayerCharacter>(GetOwner());
}


// Called every frame
void UACThrowerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TimeSinceLastThrown += DeltaTime;
}

void UACThrowerComponent::Launch()
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
			AAPlayerCharacterController* Controller = Cast<AAPlayerCharacterController>(GetWorld()->GetFirstPlayerController());

			const FRotator SpawnRotation = Controller->PlayerCameraManager->GetCameraRotation() + FRotator(0.f, 0.f, ThrowAngle);
			const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);

			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			World->SpawnActor<AAThrowableProjectile>(Throwable, SpawnLocation, SpawnRotation, SpawnParams);
			/*PredictPath
			(
			
			);*/
			UE_LOG(LogTemp, Warning, TEXT("Throwable spawned and thrown"));
		}
	}
	else if(TimeSinceLastThrown <= ThrowCooldown)
	{
		UE_LOG(LogTemp, Warning, TEXT("Throw on cooldown"));		
	}
}

void UACThrowerComponent::ResetCooldown()
{
	TimeSinceLastThrown = 0;
}

bool UACThrowerComponent::IsOnCooldown()
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

TArray<FPredictProjectilePathPointData> UACThrowerComponent::PreditctTrajectory(
	FVector StartLocation,
	FVector LaunchVelocity,
	float ProjectileRadius,
	float MaxSimTime,
	float SimFrequency,
	bool bTracePath)
{
	TArray<FVector> PathPoints;

	FPredictProjectilePathParams PredictParams;
	PredictParams.StartLocation = StartLocation;
	PredictParams.LaunchVelocity = LaunchVelocity;
	PredictParams.ProjectileRadius = ProjectileRadius;
	PredictParams.MaxSimTime = MaxSimTime;
	PredictParams.SimFrequency = SimFrequency;
	PredictParams.bTraceWithCollision = bTracePath;
	PredictParams.bTraceWithChannel = true;
	PredictParams.TraceChannel = ECollisionChannel::ECC_Visibility;

	FPredictProjectilePathResult PredictResult;
    
	if (UGameplayStatics::PredictProjectilePath(GetWorld(), PredictParams, PredictResult))
	{
		return PredictResult.PathData;
	}

	return PredictResult.PathData;
}

void UACThrowerComponent::DrawProjectilePath()
{
	FVector StartLocation = PlayerCharacter->GetActorLocation() + MuzzleOffset; 
	FVector LaunchVelocity = PlayerCharacter->GetActorForwardVector() * 300.f; //test 

	TArray<FPredictProjectilePathPointData> PathPoints = PreditctTrajectory(StartLocation, LaunchVelocity, 5.0f, 2.0f, 60.0f, true);

	for (int i = 0; i < PathPoints.Num() - 1; i++)
	{
		DrawDebugLine(GetWorld(), PathPoints[i].Location, PathPoints[i + 1].Velocity, FColor::Red, false, -1.0f, 0, 5.0f);
		UE_LOG(LogTemp, Warning, TEXT("Drawing Projectile Trajectory"))
	}
}

