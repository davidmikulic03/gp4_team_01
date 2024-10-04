// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_Sense.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "gp4_team_01/Enemies/EnemyBase.h"
#include "gp4_team_01/Enemies/PerceptionSignal.h"

bool UBTDecorator_Sense::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const {
	if(!Super::CalculateRawConditionValue(OwnerComp, NodeMemory))
		return false;

	auto Owner = Cast<AController>(OwnerComp.GetOwner());
	AEnemyBase* Enemy = Cast<AEnemyBase>(Owner->GetPawn());

	auto TargetId = BlackboardKey.SelectedKeyName;
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();

	if(Enemy) {
		auto VisionSignals = AEnemyBase::GetVisionSignals(Enemy);
		if(VisionSignals.Num() > 0) {
			BlackboardComp->SetValueAsVector(TargetId, USignalFunctions::GetSignalOrigin(VisionSignals[0]));
			return true;
		}
		//auto LastHearingSignal = AEnemyBase::GetLastHearingSignal(Enemy);
		//BlackboardComp->SetValueAsVector(TargetId, USignalFunctions::GetSignalOrigin(LastHearingSignal));
	}
	
	return true;
}
