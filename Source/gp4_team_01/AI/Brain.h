#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "WeightedSignal.h"
#include "Brain.generated.h"

UCLASS()
class GP4_TEAM_01_API UBrain : public UObject {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void CalculateTimeInvariantSignalWeight(AActor* Target, int AtId, float DistanceExponent,
		float RecencyExponent);

	TArray<FWeightedSignal> Memory;
};
