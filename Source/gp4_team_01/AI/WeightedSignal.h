#pragma once
#include "CoreMinimal.h"
#include "gp4_team_01/Enemies/PerceptionSignal.h"

#include "WeightedSignal.generated.h"

class AEnemyBase;

USTRUCT(BlueprintType)
struct FWeightedSignal {
	GENERATED_BODY()
    
	FWeightedSignal() { }
	FWeightedSignal(FPerceptionSignal Signal, float Weight)
		: Signal(Signal), Weight(Weight) { }
	FWeightedSignal(FPerceptionSignal Signal)
		: Signal(Signal) { }

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FPerceptionSignal Signal;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Weight = 0.f;

	double Time;
};