
#include "FuzzyBrainComponent.h"

#include "EnemyAIController.h"
#include "gp4_team_01/Enemies/EnemyBase.h"


UFuzzyBrainComponent::UFuzzyBrainComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UFuzzyBrainComponent::RegisterSignalToMemory(double DeltaTime, FPerceptionSignal Signal) {
	for(int i = 0; i < Memory.Num(); i++) {
		if(Signal.Actor && Memory[i].Signal.Actor == Signal.Actor) {
			Memory[i].ResetDecay();
			IncrementCompoundingWeight(Memory[i], DeltaTime);
			return;
		}
	}
	Memory.Add(Signal);
}

float UFuzzyBrainComponent::GetRelativeWeight(AActor* Actor) const {
	if(auto inMemory = Memory.FindByPredicate([this, Actor](FWeightedSignal WeightedSignal) {
			return WeightedSignal.Signal.Actor == Actor;
	})) {
		return inMemory->GetWeight() / MaxCompoundInterest;
	}
	return 0;
}

void UFuzzyBrainComponent::See(double DeltaTime) {
	auto Controller = Cast<AEnemyAIController>(GetOwner());
	if(!Controller)
		return;
	if(auto Self = Cast<AEnemyBase>(Controller->GetPawn())){
		auto Signals = AEnemyBase::GetVisionSignals(Self);
		for (auto& Signal : Signals) {
			RegisterSignalToMemory(DeltaTime, Signal);
		}
	}
}

void UFuzzyBrainComponent::Hear(double DeltaTime) {
	auto Controller = Cast<AEnemyAIController>(GetOwner());
	if(auto Self = Cast<AEnemyBase>(Controller->GetPawn())){
		if (AEnemyBase::HasNewSignalBeenHeard(Self) ) {
			RegisterSignalToMemory(DeltaTime, AEnemyBase::GetLastHearingSignal(Self));
		}
	}
}

void UFuzzyBrainComponent::ForgetUnimportant(double DeltaTime) {
	Memory.RemoveAll([this](FWeightedSignal Signal)
				{ return Signal.GetWeight() < ForgetThreshold; });
	for (auto& WeightedSignal : Memory) {
		DecrementCompoundingWeight(WeightedSignal, DeltaTime, Params.PrejudiceDecay);
	}
}

FWeightedSignal UFuzzyBrainComponent::GetSignalOfHighestWeight() {
	FWeightedSignal Result = FWeightedSignal();
	if(Memory.Num() == 0)
		return Result;
	for (auto& WeightedSignal : Memory) {
		if(WeightedSignal.GetWeight() > Result.GetWeight())
			Result = WeightedSignal;
	}
	return Result;
}

void UFuzzyBrainComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	//Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FWeightedSignal Highest = GetSignalOfHighestWeight();
	if(Highest.IsValid() && Highest.Signal != PreviousHighestWeight.Signal) {
		PreviousHighestWeight = Highest;
		if(auto Owner = Cast<AEnemyAIController>(GetOwner()))
			Owner->OnInterestChanged(Highest);
	}
	
	UpdateWeights(DeltaTime);
	ForgetUnimportant(DeltaTime);

	See(DeltaTime);
	Hear(DeltaTime);

	for (uint64 i = 0; i < Memory.Num(); i++) {
		GEngine->AddOnScreenDebugMessage(i+200, 1.f, FColor::Emerald,
			FString::Printf(TEXT("%f"), Memory[i].GetWeight()));
	}
}

void UFuzzyBrainComponent::UpdateAnalyticWeight(FWeightedSignal& WeightedSignal, float DistanceExponent) {
	WeightedSignal.AnalyticWeight = WeightedSignal.Signal.SignalStrength;
	float Distance = FVector::Distance(GetOwner()->GetActorLocation(), USignalFunctions::GetSignalOrigin(WeightedSignal.Signal)) / 100;
	WeightedSignal.AnalyticWeight *= FMath::Exp(-Distance * DistanceExponent);
}

void UFuzzyBrainComponent::IncrementCompoundingWeight(FWeightedSignal& WeightedSignal, double DeltaTime) {
	auto Actor = WeightedSignal.Signal.Actor;
	if(Actor && !ClassPrejudice.IsEmpty()) {
		auto ActorPrejudice = ClassPrejudice.FindByPredicate([this, Actor](FWeightedClass WeightedClass)
		{ return Actor->IsA(WeightedClass.Class); });
		if(ActorPrejudice && ActorPrejudice->Weight != 0 && WeightedSignal.CompoundingWeight < MaxCompoundInterest) {
			WeightedSignal.CompoundingWeight += ActorPrejudice->Weight * DeltaTime;
			if(WeightedSignal.CompoundingWeight > MaxCompoundInterest)
				WeightedSignal.CompoundingWeight = MaxCompoundInterest;
		}
	}
}

void UFuzzyBrainComponent::DecrementCompoundingWeight(FWeightedSignal& WeightedSignal, double DeltaTime,
	float PrejudiceDecay) {
	WeightedSignal.CompoundingWeight *= FMath::Exp(-DeltaTime * PrejudiceDecay);
}

void UFuzzyBrainComponent::UpdateDecayingWeight(FWeightedSignal& WeightedSignal, double DeltaTime, float DecayExponent) {
	WeightedSignal.DecayingWeight *= FMath::Exp(-DeltaTime * DecayExponent);
}

bool UFuzzyBrainComponent::HasMemory(FPerceptionSignal Signal) {
	for(auto WeightedSignal : Memory) {
		if(WeightedSignal.Signal == Signal)
			return true;
	}
	return false;
}
