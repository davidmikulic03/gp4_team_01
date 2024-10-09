#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeightedSignal.h"
#include "FuzzyBrainComponent.generated.h"

USTRUCT(BlueprintType)
struct FSignalWeightParameters {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float PrejudiceDecay = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DistanceExponent = 1.f;
};

USTRUCT(Blueprintable, meta=(CollapseCategories))
struct FSignalWeightThresholds {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = 0))
		float WeakSignalThreshold = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = 0))
		float MediumSignalThreshold = 30.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = 0))
		float StrongSignalThreshold = 60.f;
};

UCLASS(BlueprintType, Blueprintable)
class GP4_TEAM_01_API UFuzzyBrainComponent : public UActorComponent {
	GENERATED_BODY()

public:
	UFuzzyBrainComponent();
	
	void RegisterSignalToMemory(double DeltaTime, FPerceptionSignal Signal);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE float GetWeight(FWeightedSignal WeightedSignal) const noexcept { return WeightedSignal.GetWeight(); }

	UFUNCTION(BlueprintCallable)
		bool TryResolvePointOfInterest(FPerceptionSignal Signal);
	UFUNCTION(BlueprintCallable)
		bool IsResolvable(FPerceptionSignal Signal, FWeightedSignal& InMemory) const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
		float GetNormalizedWeight(AActor* Actor) const;

	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brain")
		TArray<FWeightedClass> ClassPrejudice;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brain")
		FSignalWeightParameters Params;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brain")
		float ForgetThreshold = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brain", meta = (UIMin = 0))
		float MaxInterest = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brain")
		FSignalWeightThresholds SignalWeightThresholds;

protected:
	void UpdateAnalyticWeight(FWeightedSignal& WeightedSignal, float DistanceExponent);
	void IncrementCompoundingWeight(FWeightedSignal& WeightedSignal, double DeltaTime);
	void DecrementCompoundingWeight(FWeightedSignal& WeightedSignal, double DeltaTime, float PrejudiceDecay);
	bool HasMemory(FPerceptionSignal Signal);
	void See(double DeltaTime);
	void Hear(double DeltaTime);
	void UpdateSignal(FWeightedSignal& WeightedSignal, double DeltaTime);
	FORCEINLINE void ForgetUnimportant();
	uint32 GetSignalIdOfHighestWeight();
	

	uint32 PreviousHighestWeightId = INDEX_NONE;
	TArray<FWeightedSignal> Memory;
};
