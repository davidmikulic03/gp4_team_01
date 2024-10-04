#include "InteractableTargetDoor.h"


AInteractableTargetDoor::AInteractableTargetDoor() {
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AInteractableTargetDoor::BeginPlay() {
	Super::BeginPlay();

	StartingPosition = GetActorLocation();
}

// Called every frame
void AInteractableTargetDoor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AInteractableTargetDoor::OnInteract() {
	//TODO: make this happen gradually, this is just a tp for now
	SetActorLocation(StartingPosition + FVector(XTargetOffest, YTargetOffest, ZTargetOffest));
}

void AInteractableTargetDoor::OnUnInteract() {
	SetActorLocation(StartingPosition);
}

