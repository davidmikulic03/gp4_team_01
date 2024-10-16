// Fill out your copyright notice in the Description page of Project Settings.


#include "PetrifyGunComponent.h"
#include "PlayerCharacter.h"
#include "gp4_team_01/Enviroment/Interactable.h"

// Sets default values for this component's properties
UPetrifyGunComponent::UPetrifyGunComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComp");
	
}


// Called when the game starts
void UPetrifyGunComponent::BeginPlay()
{
	Super::BeginPlay();
	TimeSinceLastShot = 1000.f;
	// ...
	Controller = Cast<APlayerCharacterController>(GetWorld()->GetFirstPlayerController());
}


// Called every frame
void UPetrifyGunComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TimeSinceLastShot += DeltaTime;

}

void UPetrifyGunComponent::TryFirePetrifyGun()
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
		FVector EndLocation = StartLocation + (StartRotation.Vector() * TraceLength);
		

		bool bTraceHit = GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation + MuzzleOffset, 
			EndLocation,
			ECC_WorldDynamic, 
			CollisionParams);
		if (bTraceHit)
		{
			if (HitResult.GetActor() && HitResult.GetActor()->Implements<UPetrifiable>())
			{
				auto asPetrifiable = Cast<IPetrifiable>(HitResult.GetActor());
				//petrify
				asPetrifiable->Petrify(HitResult.GetActor(), Cast<APlayerCharacter>(GetOwner()));
			}

			AInteractable* HitInteractable = Cast<AInteractable>(HitResult.GetActor());
			if(HitInteractable)
			{
				HitInteractable->Break();
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
