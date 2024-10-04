// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_PetrifyGun.h"

// Sets default values for this component's properties
UAC_PetrifyGun::UAC_PetrifyGun()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComp");
	
}


// Called when the game starts
void UAC_PetrifyGun::BeginPlay()
{
	Super::BeginPlay();
	TimeSinceLastShot = 1000.f;
	// ...
	Controller = Cast<AAPlayerCharacterController>(GetWorld()->GetFirstPlayerController());
}


// Called every frame
void UAC_PetrifyGun::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TimeSinceLastShot += DeltaTime;

}

void UAC_PetrifyGun::TryFirePetrifyGun()
{
	if(TimeSinceLastShot < ShotCooldown)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot fire gun. Cooldown in progress"))
	}
	else if(TimeSinceLastShot >= ShotCooldown)
	{
		//fire
		//linetrace
		//TODO: fine tune it.
		FVector StartLocation;
		FRotator StartRotation;

		Controller->GetPlayerViewPoint(StartLocation, StartRotation);
		
		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(Controller->GetPawn());
		FVector EndLocation = StartLocation + MuzzleOffset + (StartRotation.Vector() * TraceLength);
		

		bool bTraceHit = GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation + MuzzleOffset, 
			EndLocation,
			ECC_WorldDynamic, 
			CollisionParams);
		DrawDebugLine(GetWorld(), StartLocation + MuzzleOffset, EndLocation, FColor::Red, false, 3.f, 0, 5.f);
		if (bTraceHit)
		{
			AActor* HitActor = HitResult.GetActor(); 
			if (HitActor->IsA(AEnemyBase::StaticClass()) || HitActor->GetClass()->IsChildOf<AEnemyBase>())
			{
				//petrify
				UE_LOG(LogTemp, Warning, TEXT("Hit something - %s"), *HitActor->GetName());
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Hit Something - %s"), *HitActor->GetName());
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit nothing"));
		}

;		UE_LOG(LogTemp, Warning, TEXT("PetrifyGun Fired"));
		TimeSinceLastShot = 0.f;
	}

}

