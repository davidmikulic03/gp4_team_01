
#include "FuzzyBrainComponent.h"

#include "DetectionModifier.h"
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

bool UFuzzyBrainComponent::TryResolvePointOfInterest(FPerceptionSignal Signal) {
	FWeightedSignal InArray;
	if(IsResolvable(Signal, InArray)) {
		Memory.Remove(InArray);
		return true;
	}
	return false;
}

bool UFuzzyBrainComponent::IsResolvable(FPerceptionSignal Signal, FWeightedSignal& InMemory) const {
	auto InArray = Memory.FindByPredicate([Signal](FWeightedSignal s)
		{ return s.Signal == Signal; });
	if (!InArray || !InArray->IsResolvable())
		return false;
	InMemory = *InArray;
	return true;
}

float UFuzzyBrainComponent::GetNormalizedWeight(AActor* Actor) const {
	if(auto inMemory = Memory.FindByPredicate([this, Actor](FWeightedSignal WeightedSignal) {
			return WeightedSignal.Signal.Actor == Actor;
		})) {
		float Result = inMemory->GetWeight() / MaxInterest;
		return Result < 1.f ? Result > 0 ? Result : 0.f : 1.f;
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

void UFuzzyBrainComponent::UpdateSignal(FWeightedSignal& WeightedSignal, double DeltaTime) {
	auto Actor = WeightedSignal.Signal.Actor;
	if(Actor && WeightedSignal.GetWeight() > SignalWeightThresholds.StrongSignalThreshold)
		WeightedSignal.Signal.SignalOrigin = Actor->GetActorLocation();
}

void UFuzzyBrainComponent::ForgetUnimportant() {
	int Num = Memory.Num();
	for(int i = 0; i < Num; i++) {
		if(Memory[i].GetWeight() < ForgetThreshold) {
			Memory.RemoveAt(i);
			if(PreviousHighestWeightId >= static_cast<uint32>(i))
				PreviousHighestWeightId--;
			i--;
			Num--;
		}
	}
}

uint32 UFuzzyBrainComponent::GetSignalIdOfHighestWeight() {
	uint32 Result = INDEX_NONE;
	for (int Id = 0; Id < Memory.Num(); Id++) {
		if(Result == INDEX_NONE || Memory[Id].GetWeight() > Memory[Result].GetWeight())
			Result = Id;
	}
	return Result;
}

void UFuzzyBrainComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	//Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	uint32 HighestId = GetSignalIdOfHighestWeight();
	if(HighestId != INDEX_NONE
		&& ((PreviousHighestWeightId == INDEX_NONE || PreviousHighestWeightId > static_cast<uint32>(Memory.Num()))
		|| Memory[HighestId].Signal != Memory[PreviousHighestWeightId].Signal)) {
		PreviousHighestWeightId = HighestId;
		if(auto Owner = Cast<AEnemyAIController>(GetOwner()))
			Owner->OnInterestChanged(Memory[HighestId]);
	}

	for(auto& WeightedSignal : Memory) {
		UpdateAnalyticWeight(WeightedSignal, Params.DistanceExponent);
		UpdateSignal(WeightedSignal, DeltaTime);
		if(!WeightedSignal.bPositiveSlopeSign)
			DecrementCompoundingWeight(WeightedSignal, DeltaTime, Params.PrejudiceDecay);
		WeightedSignal.bPositiveSlopeSign = false;
	}
	ForgetUnimportant();

	See(DeltaTime);
	Hear(DeltaTime);

	for (uint64 i = 0; i < Memory.Num(); i++) {
		GEngine->AddOnScreenDebugMessage(i+200, DeltaTime, FColor::Emerald,
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
		float CurrentWeight = WeightedSignal.GetWeight();
		if(ActorPrejudice && ActorPrejudice->Weight != 0 && CurrentWeight < MaxInterest) {
			float Increment = ActorPrejudice->Weight * DeltaTime;
			auto a = WeightedSignal.Signal.Actor;
			
			if(a) { if(auto DetectionModifier = Cast<UDetectionModifier>(a->GetComponentByClass(UDetectionModifier::StaticClass())))
				Increment *= DetectionModifier->DefaultSignalModifier; }
			WeightedSignal.CompoundingWeight += Increment;
			WeightedSignal.bPositiveSlopeSign = true;
		}
		else if(CurrentWeight > MaxInterest) {
			float NewCompoundWeight = MaxInterest / WeightedSignal.AnalyticWeight;
			if(NewCompoundWeight >= 0)
				WeightedSignal.CompoundingWeight = NewCompoundWeight;
		}
	}
}

void UFuzzyBrainComponent::DecrementCompoundingWeight(FWeightedSignal& WeightedSignal, double DeltaTime,
	float PrejudiceDecay) {
	WeightedSignal.CompoundingWeight *= FMath::Exp(-DeltaTime * PrejudiceDecay);
}


bool UFuzzyBrainComponent::HasMemory(FPerceptionSignal Signal) {
	for(auto WeightedSignal : Memory) {
		if(WeightedSignal.Signal == Signal)
			return true;
	}
	return false;
}
