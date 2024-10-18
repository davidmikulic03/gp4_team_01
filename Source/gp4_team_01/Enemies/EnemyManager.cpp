#include "EnemyManager.h"

#include "EnemyBase.h"
#include "FMODBlueprintStatics.h"
#include "AI/EnemyAIController.h"
#include "AI/FuzzyBrainComponent.h"

AEnemyManager::AEnemyManager() {
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyManager::Tick(float DeltaSeconds) {
	auto Highest = GetHighestSeverity();
	if(Highest != LastHighestSeverity) {
		float asFloat;
		switch (Highest) {
		case ESignalSeverity::Weak:
			asFloat = 2.f;
			break;
		case ESignalSeverity::Medium:
			asFloat = 2.f;
			break;
		case ESignalSeverity::Strong:
			asFloat = 3.f;
			break;
		default: asFloat = 1.f; break;
		}
		UFMODBlueprintStatics::SetGlobalParameterByName(FName(FString(TEXT("Suspicion"))), asFloat);
	}
	LastHighestSeverity = Highest;
}

void AEnemyManager::Register(AEnemyBase* Self) {
	if(auto Controller = Cast<AEnemyAIController>(Self->GetController())) {
		Brains.Add(Controller->Brain);
		Enemies.Add(Self);
	}
}

void AEnemyManager::RegisterSeverityChange(ESignalSeverity Severity) {
	//if(Severity > GlobalHighestSeverity) 
	//	GlobalHighestSeverity = Severity;
	//else if(Severity < GlobalLowestSeverity)
	//	GlobalLowestSeverity = Severity;
}

void AEnemyManager::ResetEnemyStates() {
	
}

ESignalSeverity AEnemyManager::GetHighestSeverity() {
	ESignalSeverity Result = ESignalSeverity::Nonperceptible;
	for (auto Brain : Brains) {
		if(static_cast<int>(Brain->GetLastSeverity()) > static_cast<int>(Result))
			Result = Brain->GetLastSeverity();
	}
	return Result;
}
