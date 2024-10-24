#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "EnemyManager.generated.h"

class AFMODAmbientSound;
enum class ESignalSeverity : uint8;
class UFuzzyBrainComponent;
class AEnemyBase;

UCLASS()
class GP4_TEAM_01_API AEnemyManager : public AActor {
	GENERATED_BODY()
public:
	AEnemyManager();
	
	virtual void Tick(float DeltaSeconds) override;
	
	UFUNCTION(BlueprintCallable)
		void LoadEnemyStates();
	UFUNCTION(BlueprintCallable)
		bool SaveEnemyStates();
	
	void Register(AEnemyBase* Self);
	void RegisterSeverityChange(ESignalSeverity Severity);

	UPROPERTY(EditInstanceOnly)
		AFMODAmbientSound* MusicActor;
private:
	ESignalSeverity GetHighestSeverity();
	
	TArray<AEnemyBase*> Enemies;
	TArray<UFuzzyBrainComponent*> Brains;
	TArray<FTransform> EnemyTransforms;

	ESignalSeverity LastHighestSeverity;
};
