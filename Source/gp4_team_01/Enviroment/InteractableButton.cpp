#include "InteractableButton.h"


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
	if(bDoesResetAfterCooldown && bIsPressed) {
		TimeSpentPressed += DeltaTime;
		if(TimeSpentPressed >= ResetCooldown) {
			bIsPressed = false;
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
	IInteractable::Break();
	//TODO: change mesh/shader to show it's broken
}

void AInteractableButton::ActivateTarget() {
	//TODO: do stuff to act on the InteractionTarget
}

void AInteractableButton::DeactivateTarget() {
	//TODO: undo stuff to act on the InteractionTarget
}

