// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "EnemyAIController.generated.h"


UCLASS()
class GP4_TEAM_01_API AEnemyAIController : public AAIController {
	GENERATED_BODY()

public:
	AEnemyAIController();

	UFUNCTION(BlueprintImplementableEvent)
		void OnInterestChanged(struct FWeightedSignal Signal);

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UBehaviorTree* BehaviorTreeRef;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Brain)
		class UFuzzyBrainComponent* Brain;
};