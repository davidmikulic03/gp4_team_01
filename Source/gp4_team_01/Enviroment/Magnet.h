#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Magnet.generated.h"

UCLASS()
class GP4_TEAM_01_API AMagnet : public AActor
{
	GENERATED_BODY()

public:
	AMagnet();

	void SetIsInteractable(bool Value);

	UFUNCTION(BlueprintImplementableEvent)
		void OnInteractable();
	UFUNCTION(BlueprintImplementableEvent)
		void OnNotInteractable();
	UFUNCTION(BlueprintImplementableEvent)
		void OnBeginTraversal();
	UFUNCTION(BlueprintImplementableEvent)
		void OnFinishTraversal();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USceneComponent* TraversalTarget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		USceneComponent* AimTarget;
protected:
	virtual void BeginPlay() override;

	bool bIsInteractable = false;
};
