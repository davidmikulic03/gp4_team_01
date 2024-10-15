#include "InteractableButton.h"

#include "InteractableTargetBase.h"


AInteractableButton::AInteractableButton() {
	PrimaryActorTick.bCanEverTick = true;
}

void AInteractableButton::BeginPlay() {
	Super::BeginPlay();

	if(!InteractionTarget)
		UE_LOG(LogTemp, Error, TEXT("ERROR: Button is missing a reference to the Actor that it needs to act on! Please plug it in the editor"))
}

void AInteractableButton::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if(bDoesResetAfterCooldown && bIsPressed && !bIsBroken) {
		TimeSpentPressed += DeltaTime;
		if(TimeSpentPressed >= ResetCooldown) {
			bIsPressed = false;
			TimeSpentPressed = 0.f;
			DeactivateTarget();
		}
	}
}

void AInteractableButton::Interact(AActor* Caller) {
	if(bIsBroken || (bDoesResetAfterCooldown && bIsPressed))
		return;

	UE_LOG(LogTemp, Warning, TEXT("%s tried to interact with me!"), *Caller->GetName());
	ActivateTarget();
	
	if(bDoesResetAfterCooldown)
		bIsPressed = true;
}

void AInteractableButton::Break() {
	Super::Break();
	//TODO: change mesh/shader to show it's broken
}

void AInteractableButton::ActivateTarget() const {
	InteractionTarget->OnInteract();
}

void AInteractableButton::DeactivateTarget() const {
	InteractionTarget->OnUnInteract();
}

