
#include "Brain.h"
#include "gp4_team_01/Enemies/EnemyBase.h"

void UBrain::CalculateTimeInvariantSignalWeight(AActor* Target, int AtId, float DistanceExponent,
	float RecencyExponent) {
	if(AtId < 0 || AtId >= Memory.Num())
		return;
	Memory[AtId].Weight = Memory[AtId].Signal.SignalStrength;
	float Distance = FVector::Distance(Target->GetActorLocation(), USignalFunctions::GetSignalOrigin(Memory[AtId].Signal)) / 100;
	Memory[AtId].Weight *= FMath::Exp(-Distance / DistanceExponent);
	Memory[AtId].Weight *= FMath::Exp(-(AtId / static_cast<float>(Memory.Num())) / RecencyExponent);
}
