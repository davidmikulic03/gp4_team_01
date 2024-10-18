#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EnemyManager.generated.h"

enum class ESignalSeverity : uint8;
class UFuzzyBrainComponent;
class AEnemyBase;

UCLASS()
class GP4_TEAM_01_API AEnemyManager : public AActor {
	GENERATED_BODY()
public:
	AEnemyManager();
	
	virtual void Tick(float DeltaSeconds) override;
	
	void Register(AEnemyBase* Self);
	void RegisterSeverityChange(ESignalSeverity Severity);
	void ResetEnemyStates();
private:
	ESignalSeverity GetHighestSeverity();
	
	TArray<AEnemyBase*> Enemies;
	TArray<UFuzzyBrainComponent*> Brains;

	ESignalSeverity LastHighestSeverity;
};
