#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableTargetBase.generated.h"

UCLASS(Abstract)
class GP4_TEAM_01_API AInteractableTargetBase : public AActor {
	GENERATED_BODY()

public:
	AInteractableTargetBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	//for some absurd reason the PURE_VIRTUAL macro doesn't seem to do its thing but we'll take it
	UFUNCTION(BlueprintCallable)
	virtual void OnInteract() PURE_VIRTUAL(AInteractableTargetBase::OnInteract, ;);

	UFUNCTION(BlueprintCallable)
	virtual void OnUnInteract() PURE_VIRTUAL(AInteractableTargetBase::OnUnInteract, ;);
};
