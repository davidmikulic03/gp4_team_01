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
	void Move(float DeltaTime);
	void FadeOpen(float DeltaTime);

protected:
	UPROPERTY(EditAnywhere, Category = "Interaction Target")
	bool bFadesOutOnInteraction = false;

	UPROPERTY(EditAnywhere, Category = "Interaction Target", meta = (EditCondition = "bFadesOutOnInteraction", EditConditionHides))
	float TimeToFadeOpen = 1.f ;
	
	UPROPERTY(EditAnywhere, Category = "Interaction Target", meta = (EditCondition = "!bFadesOutOnInteraction", EditConditionHides))
	USceneComponent* Target = nullptr;

	UPROPERTY(EditAnywhere, Category = "Interaction Target", meta = (EditCondition = "!bFadesOutOnInteraction", EditConditionHides))
	float Speed = 5.f;

	bool bIsOpening = false;

	bool bIsClosing = false;
	
	FVector StartingPosition;

	FVector TargetVector;
};
