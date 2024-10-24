#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PickupManager.generated.h"

class APickup;

UCLASS()
class GP4_TEAM_01_API UPickupManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		void SavePickupStates();
	UFUNCTION(BlueprintCallable)
		void LoadPickupStates();
	
	void Register(APickup* Pickup);
	
private:
	UPROPERTY()
	TArray<APickup*> Pickups;
	UPROPERTY()
	TArray<bool> PickupStates;
};
