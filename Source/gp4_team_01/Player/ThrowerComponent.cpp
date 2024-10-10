#include "ThrowerComponent.h"

#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStaticsTypes.h"


// Sets default values for this component's properties
UThrowerComponent::UThrowerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}


// Called when the game starts
void UThrowerComponent::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<APlayerCharacter>(GetOwner());
}


// Called every frame
void UThrowerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TimeSinceLastThrown += DeltaTime;
}

void UThrowerComponent::Launch()
{
	if(Throwable != nullptr && TimeSinceLastThrown >= ThrowCooldown)
	{
		UWorld* const World = GetWorld();
		if(World !=nullptr)
		{
			const FRotator SpawnRotation = GetComponentRotation();
			const FVector SpawnLocation = GetComponentLocation();

			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			auto Projectile = World->SpawnActor<AThrowableProjectile>(Throwable, SpawnLocation, SpawnRotation, SpawnParams);
			Projectile->GetProjectileMovement()->InitialSpeed = ThrowSpeed;
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

FPredictProjectilePathResult UThrowerComponent::PredictTrajectory(
	FVector StartLocation,
	FVector LaunchVelocity,
	float ProjectileRadius,
	float MaxSimTime,
	float SimFrequency,
	bool bTracePath)
{
	FPredictProjectilePathParams PredictParams;
	PredictParams.StartLocation = StartLocation;
	PredictParams.LaunchVelocity = LaunchVelocity;
	PredictParams.ProjectileRadius = ProjectileRadius;
	PredictParams.MaxSimTime = MaxSimTime;
	PredictParams.SimFrequency = SimFrequency;
	PredictParams.bTraceWithCollision = bTracePath;
	PredictParams.bTraceWithChannel = true;
	PredictParams.TraceChannel = ECC_Visibility;

	FPredictProjectilePathResult PredictResult;
	UGameplayStatics::PredictProjectilePath(GetWorld(), PredictParams, PredictResult);
	return PredictResult;
}

void UThrowerComponent::DrawProjectilePath(FPredictProjectilePathResult PathResult) {
	for (int i = 0; i < PathResult.PathData.Num() - 1; i++)
	{
		DrawDebugLine(GetWorld(), PathResult.PathData[i].Location, PathResult.PathData[i + 1].Location, FColor::Red, false);
		UE_LOG(LogTemp, Warning, TEXT("Drawing Projectile Trajectory"))
	}
}