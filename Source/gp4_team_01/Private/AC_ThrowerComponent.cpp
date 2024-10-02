// Fill out your copyright notice in the Description page of Project Settings.


#include "AC_ThrowerComponent.h"

// Sets default values for this component's properties
UAC_ThrowerComponent::UAC_ThrowerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MuzzleOffset = FVector(100.f, 0.f, 10.f);


}


// Called when the game starts
void UAC_ThrowerComponent::BeginPlay()
{
	Super::BeginPlay();


	
}


// Called every frame
void UAC_ThrowerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAC_ThrowerComponent::Launch()
{
	if(GetWorld()->GetFirstPlayerController()->GetPawn() == nullptr || GetWorld()->GetFirstPlayerController() == nullptr)
	{
		return;
	}

	if(Throwable != nullptr)
	{
		UWorld* const World = GetWorld();
		if(World !=nullptr)
		{
			AAPlayerCharacterController* Controller = Cast<AAPlayerCharacterController>(GetWorld()->GetFirstPlayerController());

			const FRotator SpawnRotation = Controller->PlayerCameraManager->GetCameraRotation();
			const FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);

			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			World->SpawnActor<AAThrowableProjectile>(Throwable, SpawnLocation, SpawnRotation, SpawnParams);
			UE_LOG(LogTemp, Warning, TEXT("Throwable spawned and thrown"));
		}
	}
}

