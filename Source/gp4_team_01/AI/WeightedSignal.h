#pragma once
#include "CoreMinimal.h"
#include "gp4_team_01/Enemies/PerceptionSignal.h"

#include "WeightedSignal.generated.h"

class AEnemyBase;

USTRUCT(BlueprintType)
struct FWeightedSignal {
	GENERATED_BODY()
    
	FWeightedSignal() { }
	FWeightedSignal(FPerceptionSignal Signal)
		: Signal(Signal) { }

	UPROPERTY(BlueprintReadOnly, Category = "AI|Perception|Signal")
		FPerceptionSignal Signal;

	// We need three weights for it to be non-destructive.
	float AnalyticWeight = 0.f;
	float DecayingWeight = 1.f;
	float CompoundingWeight = 0.f;
	
	FORCEINLINE void ResetDecay() noexcept { DecayingWeight = 1.f; }
	FORCEINLINE float GetWeight() const noexcept {
		return (AnalyticWeight + CompoundingWeight) * DecayingWeight;
	}

	FORCEINLINE bool operator ==(FWeightedSignal Other) const noexcept {
		return GetWeight() == Other.GetWeight();
	}
	FORCEINLINE bool operator !=(FWeightedSignal Other) const noexcept {
		return GetWeight() != Other.GetWeight();
	}
	
	FORCEINLINE bool IsValid() const {
		return *this != FWeightedSignal();
	}
};


USTRUCT(BlueprintType, Blueprintable)
struct FWeightedClass {
	GENERATED_BODY()

	FWeightedClass() {}
	FWeightedClass(TSubclassOf<AActor> Class, float Weight)
		: Class(Class), Weight(Weight) {}

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TSubclassOf<AActor> Class;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		float Weight = 1.f;
};