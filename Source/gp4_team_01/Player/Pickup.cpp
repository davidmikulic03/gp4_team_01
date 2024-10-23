// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include "gp4_team_01/Systems/PickupManager.h"

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

	if(auto g = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(GetWorld()))) {
		if(auto p = g->GetPickupManagerRef())
			p->Register(this);
	}
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APickup::Interact(AActor* Caller)
{
	if(!bEnabled)
		return;
	
	APlayerCharacter* CallerActor = Cast<APlayerCharacter>(Caller);
	if(CallerActor)
	{
		if(CallerActor->GetThrowableInventory()->CanFitMoreItemOfType(ItemType)) {
			CallerActor->GetThrowableInventory()->AddAmountToInventory(ItemType, AmountToAdd);
			SetEnabled(false);
		}
	}

	Super::Interact(Caller);
}

void APickup::SetEnabled(bool Value) {
	bEnabled = Value;
	RootComponent->SetHiddenInGame(!Value, true);
}

