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


protected:
	UPROPERTY(EditAnywhere, Category = "Interaction Target")
	USceneComponent* Target = nullptr;

	UPROPERTY(EditAnywhere, Category = "Fallable")
	float Speed = 5.f;

	bool bIsMoving = false;
	
	FVector StartingPosition;

	FVector TargetVector;
};
