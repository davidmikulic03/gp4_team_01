#include "EnemyAIController.h"
#include "FuzzyBrainComponent.h"

AEnemyAIController::AEnemyAIController() {
	Brain = CreateDefaultSubobject<UFuzzyBrainComponent>("Brain");
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyAIController::BeginPlay() {
	Super::BeginPlay();
}

void AEnemyAIController::OnPossess(APawn* InPawn) {
	if(!BehaviorTreeRef)
		UE_LOG(LogTemp, Error, TEXT("ERROR: Missing BehaviorTreeRef, please plug it in the editor!"));
	
	RunBehaviorTree(BehaviorTreeRef);
	Super::OnPossess(InPawn);
}

void AEnemyAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

