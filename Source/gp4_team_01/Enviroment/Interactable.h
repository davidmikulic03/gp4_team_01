#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

UCLASS()
class GP4_TEAM_01_API AInteractable : public AActor {
	GENERATED_BODY()

public:
	AInteractable();

	virtual void Interact(AActor* Caller) PURE_VIRTUAL(AInteractableTargetBase::OnInteract, ;);
	virtual void Break() { bIsBroken = true; } ;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	bool bIsBroken = false;
};
