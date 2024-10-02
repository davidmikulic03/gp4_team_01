#include "EnemyBase.h"
#include "SightComponent.h"


AEnemyBase::AEnemyBase() {
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyBase::Petrify(APawn* Player) {
	bIsPetrified = true;
	OnPetrify(Player);
	if(GEngine && Player)
		GEngine->AddOnScreenDebugMessage(666, 15.f, FColor::Blue,
			FString::Printf(TEXT("Enemy petrified by %s"), *Player->GetName()));
}

void AEnemyBase::Unpetrify(APawn* Player) {
	bIsPetrified = false;
	OnUnpetrify(Player);
	if(GEngine && Player)
		GEngine->AddOnScreenDebugMessage(666, 15.f, FColor::Green,
			FString::Printf(TEXT("Enemy unpetrified by %s"), *Player->GetName()));
}

void AEnemyBase::BeginPlay() {
	Super::BeginPlay();
}

void AEnemyBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	bool bIsPlayerVisible = false;
	for(auto SightComponent : SightComponents) {
		if(SightComponent->IsPlayerVisible()) {
			bIsPlayerVisible = true;
			break;
		}
	}

	GEngine->AddOnScreenDebugMessage(21, 15.f, FColor::Green,
		FString::Printf(TEXT("Player Visible: %i"), bIsPlayerVisible));
}

void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

