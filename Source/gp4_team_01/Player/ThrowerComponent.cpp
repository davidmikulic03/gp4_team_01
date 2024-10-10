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

	MuzzleOffset = FVector(300.f, 0.f, 10.f);

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

TArray<FPredictProjectilePathPointData> UThrowerComponent::PreditctTrajectory(
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
	return PredictResult.PathData;
}

void UThrowerComponent::DrawProjectilePath()
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