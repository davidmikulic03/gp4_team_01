#pragma once

#include "CoreMinimal.h"
#include "InteractableTargetBase.h"
#include "InteractableTargetDoor.generated.h"

class UNoiseDataAsset;

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
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category = "Interaction Target")
	bool bFadesOutOnInteraction = false;

	//The shader has to use this, bIsOpening and bIsClosed as parameters for the fadein/out
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction Target", meta = (EditCondition = "bFadesOutOnInteraction", EditConditionHides))
	float TimeToFadeOpen = 1.f ;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction Target", meta = (EditCondition = "!bFadesOutOnInteraction", EditConditionHides))
	USceneComponent* Target = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction Target", meta = (EditCondition = "!bFadesOutOnInteraction", EditConditionHides))
	float Speed = 5.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = "Interaction Target")
	bool bIsOpening = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction Target")
	bool bIsClosing = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction Target")
		UNoiseDataAsset* NoiseOnBreak;
	
	FVector StartingPosition;

	FVector TargetVector;

	UPROPERTY(BlueprintReadOnly)
	float CurrentFadeTimer = .0f;
};
