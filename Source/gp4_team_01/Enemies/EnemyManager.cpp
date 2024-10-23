#include "EnemyManager.h"

#include "EnemyBase.h"
#include "FMODAmbientSound.h"
#include "FMODBlueprintStatics.h"
#include "AI/EnemyAIController.h"
#include "AI/FuzzyBrainComponent.h"

AEnemyManager::AEnemyManager() {
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyManager::Tick(float DeltaSeconds) {
	auto Highest = GetHighestSeverity();

	float asFloat;
	switch (Highest) {
	case ESignalSeverity::Weak:
		asFloat = 1.f;
		break;
	case ESignalSeverity::Medium:
		asFloat = 1.f;
		break;
	case ESignalSeverity::Strong:
		asFloat = 2.f;
		break;
	default:
		asFloat = 0.f;
		break; 
	}
	UFMODBlueprintStatics::SetGlobalParameterByName(FName(FString(TEXT("Suspicion"))), asFloat);
	
	LastHighestSeverity = Highest;
}

void AEnemyManager::LoadEnemyStates() {
	for(int i = 0; i < Enemies.Num(); i++) {
		Brains[i]->Reset();
		Enemies[i]->LoadState();
	}
	if(MusicActor)
		MusicActor->Reset();
	LastHighestSeverity = ESignalSeverity::Nonperceptible;
}

bool AEnemyManager::SaveEnemyStates() {
	if(GetHighestSeverity() == ESignalSeverity::Strong)
		return false;
	else {
		//for(int i = 0; i < Enemies.Num(); i++) {
		//	Enemies[i]->SaveState();
		//}
		return true;
	}
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


ESignalSeverity AEnemyManager::GetHighestSeverity() {
	ESignalSeverity Result = ESignalSeverity::Nonperceptible;
	for (auto Brain : Brains) {
		if(static_cast<int>(Brain->GetLastSeverity()) > static_cast<int>(Result))
			Result = Brain->GetLastSeverity();
	}
	return Result;
}
