#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "InteractableButton.generated.h"

class AInteractableTargetBase;

UCLASS(Abstract)
class GP4_TEAM_01_API AInteractableButton : public AInteractable {
	GENERATED_BODY()

public:
	AInteractableButton();
	
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	virtual void Interact(AActor* Caller) override;

	UFUNCTION(BlueprintCallable)
	virtual void Break() override;
	
private:
	//TERRIBLE NAMES!!!
	void ActivateTarget() const;
	void DeactivateTarget() const;
	
private:
	//TODO: maybe this guy should also be its own interface? IInteractionTarget?
	UPROPERTY(EditAnywhere, Category = "Interaction")
	AInteractableTargetBase* InteractionTarget = nullptr;
	
	UPROPERTY(EditAnywhere, Category = "Interaction")
	bool bDoesResetAfterCooldown = true;

	UPROPERTY(EditAnywhere, Category = "Interaction", meta = (EditCondition = "bDoesResetAfterCooldown", EditConditionHides))
	float ResetCooldown = 10.f;
	
	bool bIsPressed = false;
	float TimeSpentPressed = 0.f;
};
