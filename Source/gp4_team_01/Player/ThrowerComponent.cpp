#include "ThrowerComponent.h"

#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"


// Sets default values for this component's properties
UThrowerComponent::UThrowerComponent()
{
	Spline = CreateDefaultSubobject<USplineComponent>("Prediction Spline");
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UThrowerComponent::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<APlayerCharacter>(GetOwner());
	
	for(int i = 0; i < PredictionFrequency * PredictionTime; i++) {
		auto NewComponent = Cast<USplineMeshComponent>(GetOwner()->AddComponentByClass(USplineMeshComponent::StaticClass(), true, FTransform::Identity, false));
		NewComponent->SetMobility(EComponentMobility::Movable);
		NewComponent->SetStaticMesh(SplineMesh);
		NewComponent->SetVisibility(false);
		//NewComponent->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		SplineMeshes.Add(NewComponent);
	}
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

FPredictProjectilePathResult UThrowerComponent::PredictTrajectory()
{
	FPredictProjectilePathParams PredictParams;
	PredictParams.StartLocation = GetComponentLocation();
	PredictParams.LaunchVelocity = GetForwardVector() * ThrowSpeed;
	PredictParams.ProjectileRadius = ProjectileRadius;
	PredictParams.MaxSimTime = PredictionTime;
	PredictParams.SimFrequency = PredictionFrequency;
	PredictParams.bTraceWithCollision = true;
	PredictParams.bTraceWithChannel = true;
	PredictParams.TraceChannel = ECC_WorldStatic;
	PredictParams.ActorsToIgnore = { GetOwner() };

	FPredictProjectilePathResult PredictResult;
	UGameplayStatics::PredictProjectilePath(GetWorld(), PredictParams, PredictResult);
	return PredictResult;
}

void UThrowerComponent::DrawProjectilePath(FPredictProjectilePathResult PathResult) {
	if(!SplineMesh) return;
	for (int i = 0; i < FMath::Max(PathResult.PathData.Num() - 1, SplineMeshes.Num()); i++) {
		if(i + 1 < PathResult.PathData.Num()) {
			SplineMeshes[i]->SetVisibility(true);
			SplineMeshes[i]->SetStartAndEnd(
				PathResult.PathData[i].Location, PathResult.PathData[i].Velocity.GetSafeNormal(),
				PathResult.PathData[i+1].Location, PathResult.PathData[i+1].Velocity.GetSafeNormal());
		}
		else {
			SplineMeshes[i]->SetVisibility(false);
		}
	}
}

void UThrowerComponent::HideProjectilePath() {
	for (int i = 0; i < SplineMeshes.Num(); i++) {
		SplineMeshes[i]->SetVisibility(false);
	}
}
