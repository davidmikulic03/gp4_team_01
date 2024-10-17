#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeightedSignal.h"
#include "SignalSeverity.h"
#include "FuzzyBrainComponent.generated.h"


class AEnemyAIController;

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
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
		FWeightedSignal GetCurrentMostInterestingSignal() const { return Memory[HighestWeightId]; };
	
	UFUNCTION(BlueprintCallable)
		ESignalSeverity GetSeverity(FWeightedSignal WeightedSignal) const noexcept;

	UFUNCTION(BlueprintCallable)
		ESignalSeverity GetSeverityFromWeight(float Weight) const noexcept;
	
	UFUNCTION(BlueprintCallable, DisplayName="Get Severity (Branching)", meta=(ExpandEnumAsExecs="Branches"))
		void GetSeverity_Branching(FWeightedSignal WeightedSignal, ESignalSeverity& Branches);
	UFUNCTION(BlueprintCallable)
		bool IsValid(FWeightedSignal WeightedSignal) const;
	UFUNCTION(BlueprintCallable, DisplayName="Is Valid (Branching)", meta=(ExpandBoolAsExecs="Result"))
		void IsValid_Branching(FWeightedSignal WeightedSignal, bool& Result);
	
	UFUNCTION(BlueprintCallable)
		bool TryResolvePointOfInterest(FPerceptionSignal Signal);
	UFUNCTION(BlueprintCallable)
		bool IsResolvable(FPerceptionSignal Signal, FWeightedSignal& InMemory) const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
		float GetNormalizedWeight(AActor* Actor) const;

	FORCEINLINE void SetIsThinking(bool Value) noexcept { bIsThinking = Value; }
	
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
	virtual void BeginPlay() override;
	
	void RegisterSignalToMemory(double DeltaTime, FPerceptionSignal Signal);
	void IncrementCompoundingWeight(FWeightedSignal& WeightedSignal, double DeltaTime);
	void Decrement(FWeightedSignal& WeightedSignal, double DeltaTime);
	bool HasMemory(FPerceptionSignal Signal) const;
	void See(double DeltaTime);
	void Hear(double DeltaTime);
	void UpdateSignal(FWeightedSignal& WeightedSignal, double DeltaTime);
	FORCEINLINE void ForgetUnimportant();
	uint32 GetSignalIdOfHighestWeight();
	void UpdateEnemyState() const;
	

	uint32 HighestWeightId = INDEX_NONE;
	TArray<FWeightedSignal> Memory;

	AEnemyAIController* Controller;
	AEnemyBase* Body;

	ESignalSeverity LastRecordedSeverity = ESignalSeverity::Nonperceptible;
	bool bIsThinking = true;
};
