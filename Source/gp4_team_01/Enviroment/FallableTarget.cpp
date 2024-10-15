#include "FallableTarget.h"

#include "gp4_team_01/Enemies/EnemyBase.h"
#include "Kismet/KismetMathLibrary.h"


AFallableTarget::AFallableTarget() {

	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFallableTarget::BeginPlay() {
	Super::BeginPlay();

	bIsMoving = false;
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

	bIsMoving = false;

	if(bKillsEnemyOnFall)
		EnemyToKill->OnDeath(this);

	//TODO: handle graphics for the break
	Destroy();
}

