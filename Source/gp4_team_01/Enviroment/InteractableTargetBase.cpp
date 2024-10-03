 #include "InteractableTargetBase.h"

AInteractableTargetBase::AInteractableTargetBase() {
	PrimaryActorTick.bCanEverTick = true;
}

void AInteractableTargetBase::BeginPlay() {
	Super::BeginPlay();
}

void AInteractableTargetBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

