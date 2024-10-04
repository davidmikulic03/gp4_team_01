#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_Blackboard.h"
#include "BTDecorator_Sense.generated.h"

UCLASS(BlueprintType)
class GP4_TEAM_01_API UBTDecorator_Sense : public UBTDecorator_Blackboard
{
	GENERATED_BODY()

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
