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
	FVector TargetOffset = FVector(0.f, 0.f, 0.f);

	FVector StartingPosition;
};
