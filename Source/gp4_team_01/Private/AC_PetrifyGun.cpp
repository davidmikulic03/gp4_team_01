// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_PetrifyGun.h"

// Sets default values for this component's properties
UAC_PetrifyGun::UAC_PetrifyGun()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MuzzleOffset = FVector(100.f, 0.f, 15.f);
}


// Called when the game starts
void UAC_PetrifyGun::BeginPlay()
{
	Super::BeginPlay();
	TimeSinceLastShot = 1000.f;
	// ...
	
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
		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(GetWorld()->GetFirstPlayerController()->GetPawn());

		bool bTraceHit = GetWorld()->LineTraceSingleByChannel(HitResult,
			MuzzleOffset,
			GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorForwardVector(),
			ECC_Visibility, 
			CollisionParams);

		if(bTraceHit)
		{
			//petrify
			UE_LOG(LogTemp, Warning, TEXT("Hit Something"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit nothing"));
		}

;		UE_LOG(LogTemp, Warning, TEXT("PetrifyGun Fired"));
		TimeSinceLastShot = 0.f;
	}

}

