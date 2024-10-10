﻿#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeightedSignal.h"
#include "FuzzyBrainComponent.generated.h"


USTRUCT(Blueprintable, meta=(CollapseCategories))
struct FSignalWeightThresholds {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = 0))
		float WeakSignalThreshold = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = 0))
		float MediumSignalThreshold = 0.3f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = 0))
		float StrongSignalThreshold = 0.6f;
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
		float DefaultPrejudice = 0.1f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brain")
		float PrejudiceDecay = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brain")
		float ForgetThreshold = 0.01f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brain", meta = (UIMin = 0))
		float MaxInterest = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Brain")
		FSignalWeightThresholds SignalWeightThresholds;

protected:
	void IncrementCompoundingWeight(FWeightedSignal& WeightedSignal, double DeltaTime);
	void Decrement(FWeightedSignal& WeightedSignal, double DeltaTime);
	bool HasMemory(FPerceptionSignal Signal);
	void See(double DeltaTime);
	void Hear(double DeltaTime);
	void UpdateSignal(FWeightedSignal& WeightedSignal, double DeltaTime);
	FORCEINLINE void ForgetUnimportant();
	uint32 GetSignalIdOfHighestWeight();
	

	uint32 PreviousHighestWeightId = INDEX_NONE;
	TArray<FWeightedSignal> Memory;
};
