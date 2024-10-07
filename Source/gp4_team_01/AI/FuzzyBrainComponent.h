#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeightedSignal.h"
#include "FuzzyBrainComponent.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct FSignalWeightParameters {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float PrejudiceDecay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DistanceExponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DecayExponent;
};

UCLASS(BlueprintType, Blueprintable)
class GP4_TEAM_01_API UFuzzyBrainComponent : public UActorComponent {
	GENERATED_BODY()

public:
	UFuzzyBrainComponent();
	
	void RegisterSignalToMemory(double DeltaTime, FPerceptionSignal Signal);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetWeight(FWeightedSignal WeightedSignal) const noexcept { return WeightedSignal.GetWeight(); }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetRelativeWeight(AActor* Actor) const;

	void See(double DeltaTime);
	void Hear(double DeltaTime);
	FORCEINLINE void UpdateWeights(double DeltaTime) {
		for(auto& WeightedSignal : Memory) {
			UpdateAnalyticWeight(WeightedSignal, Params.DistanceExponent);
			UpdateDecayingWeight(WeightedSignal, DeltaTime, Params.DecayExponent);
		}
	}
	FORCEINLINE void ForgetUnimportant(double DeltaTime);
	FWeightedSignal GetSignalOfHighestWeight();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Brain)
		TArray<FWeightedClass> ClassPrejudice;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Brain)
		FSignalWeightParameters Params;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Brain)
		float ForgetThreshold = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Brain, meta = (UIMin = 0))
		float MaxCompoundInterest = 10.f;

protected:
	void UpdateAnalyticWeight(FWeightedSignal& WeightedSignal, float DistanceExponent);
	void IncrementCompoundingWeight(FWeightedSignal& WeightedSignal, double DeltaTime);
	void DecrementCompoundingWeight(FWeightedSignal& WeightedSignal, double DeltaTime, float PrejudiceDecay);
	void UpdateDecayingWeight(FWeightedSignal& WeightedSignal, double DeltaTime, float DecayExponent);
	bool HasMemory(FPerceptionSignal Signal);

	FWeightedSignal PreviousHighestWeight;
	TArray<FWeightedSignal> Memory;
};
