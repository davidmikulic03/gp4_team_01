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

	UFUNCTION(BlueprintCallable)
	void SetInteractable(bool Value) {
		if(Value)
			OnInteractable();
		else
			OnNotInteractable();
	}
	
	UFUNCTION(BlueprintImplementableEvent)
		void OnInteract(AActor* Caller);
	UFUNCTION(BlueprintImplementableEvent)
		void OnInteractable();
	UFUNCTION(BlueprintImplementableEvent)
		void OnNotInteractable();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Tooltip;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText TextOnInteract;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	bool bIsBroken = false;
};
