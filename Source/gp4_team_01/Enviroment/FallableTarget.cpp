#include "FallableTarget.h"

#include "GameFramework/GameModeBase.h"
#include "gp4_team_01/Enemies/EnemyBase.h"
#include "gp4_team_01/Systems/MainGameMode.h"
#include "gp4_team_01/Systems/NoiseSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


AFallableTarget::AFallableTarget() {

	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFallableTarget::BeginPlay() {
	Super::BeginPlay();

	bIsOpening = false;
}

void AFallableTarget::OnInteract() {
	Super::OnInteract();
}

void AFallableTarget::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if(GetActorLocation() == TargetVector)
		OnBreak();
}

void AFallableTarget::OnBreak() {
	UE_LOG(LogTemp, Warning, TEXT("Fallable broke!"));
	
	bIsOpening = false;

	if(bKillsEnemyOnFall)
		EnemyToKill->Die(this);

	if(auto g = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(GetWorld()))) {
		g->GetNoiseSystemRef()->RegisterNoiseEvent(NoiseOnBreak, TargetVector);
	}
	
	FallableBreakEvent();
	//TODO: handle graphics for the break
	Destroy();
}

