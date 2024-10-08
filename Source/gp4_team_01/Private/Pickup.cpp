// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"


// Sets default values
APickup::APickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APickup::Interact(AActor* Caller)
{
	if(Caller->IsA(ACPlayerCharacter::StaticClass()))
	{
		Cast<ACPlayerCharacter>(Caller)->GetThrowableInventory()->AddAmountToInventory(AmountToAdd);
		Destroy();
	}
}

//i can't remember why, safety I guess?
bool APickup::GetIsThrowable()
{
	return bIsThrowable;
}


