#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

UCLASS()
class GP4_TEAM_01_API AInteractable : public AActor {
	GENERATED_BODY()

public:
	AInteractable();

	virtual void Interact(AActor* Caller) { OnInteract(Caller); };
	virtual void Break() { bIsBroken = true; } ;

	UFUNCTION(BlueprintImplementableEvent)
		void OnInteract(AActor* Caller);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	bool bIsBroken = false;
};
