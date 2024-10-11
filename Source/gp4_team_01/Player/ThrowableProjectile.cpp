// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrowableProjectile.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AThrowableProjectile::AThrowableProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AThrowableProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 1500.f;
	ProjectileMovement->MaxSpeed = 2000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void AThrowableProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	if ((OtherActor != nullptr) && (OtherActor != this))
	{
		if(NoiseDataAsset != nullptr && (GetVelocity().Length() >= 1000)) //TODO: the hardcoded 1000 is just to make sure it doesn't keep making noise with every microbounce, let's get rid of this
		{
			GenerateNoise(NoiseDataAsset, GetActorLocation());
		}
		
	}
}

// Called when the game starts or when spawned
void AThrowableProjectile::BeginPlay()
{
	Super::BeginPlay();
	NoiseSystem = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->GetNoiseSystemRef();
}

// Called every frame
void AThrowableProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AThrowableProjectile::GenerateNoise(UNoiseDataAsset* Asset, FVector Location)
{
	NoiseSystem->RegisterNoiseEvent(Asset, Location);
}



