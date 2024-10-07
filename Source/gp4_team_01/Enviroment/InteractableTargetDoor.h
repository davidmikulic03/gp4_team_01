#pragma once

#include "CoreMinimal.h"
#include "InteractableTargetBase.h"
#include "InteractableTargetDoor.generated.h"

UCLASS()
class GP4_TEAM_01_API AInteractableTargetDoor : public AInteractableTargetBase {
	GENERATED_BODY()

public:
	AInteractableTargetDoor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void OnInteract() override;

	virtual void OnUnInteract() override;


private:
	UPROPERTY(EditAnywhere, Category = "Interaction Target")
	float ZTargetOffest = .0f;

	UPROPERTY(EditAnywhere, Category = "Interaction Target")
	float XTargetOffest = .0f;

	UPROPERTY(EditAnywhere, Category = "Interaction Target")
	float YTargetOffest = .0f;

	FVector StartingPosition;
};
