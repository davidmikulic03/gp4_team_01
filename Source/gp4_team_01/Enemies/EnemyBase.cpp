#include "EnemyBase.h"
#include "SightComponent.h"
#include "PerceptionSignal.h"
#include "Kismet/GameplayStatics.h"


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

bool AEnemyBase::IsActorInView(AActor* Actor, float& DetectionRate) {
	DetectionRate = 0.f;
	for(auto SightComponent : SightComponents) {
		float currentComponentDetectionRate;
		if(SightComponent->IsActorVisible(Actor, currentComponentDetectionRate)) {
			if(currentComponentDetectionRate > DetectionRate)
				DetectionRate = currentComponentDetectionRate;
		}
	}
	return DetectionRate > 0;
}

TArray<AActor*> AEnemyBase::GetVisibleActorCandidates() {
	return GetVisibleActorCandidatesOfClass(AActor::StaticClass());
}

TArray<AActor*> AEnemyBase::GetVisibleActorCandidatesOfClass(TSubclassOf<AActor> Class) {
	TArray<AActor*> Candidates;
	for (auto SightComponent : SightComponents) {
		for (auto Candidate : SightComponent->GetActorsInVisionCone()) {
			if(Candidate->IsA(Class))
				Candidates.AddUnique(Candidate);
		}
	}
	return Candidates;
}

bool AEnemyBase::IsPlayerInView(float& SignalStrength) {
	AActor* Player = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn();
	return IsActorInView(Player, SignalStrength);
}

TArray<FPerceptionSignal> AEnemyBase::GetActorsOfClassInView(TSubclassOf<AActor> Class) {
	TArray<FPerceptionSignal> Result;
	for(auto Actor : GetVisibleActorCandidatesOfClass(Class)) {
		float DetectionRate;
		if(IsActorInView(Actor, DetectionRate))
			Result.Add(FPerceptionSignal(DetectionRate, Actor));
	}
	return Result;
}

TArray<FPerceptionSignal> AEnemyBase::GetActorsInView() {
	return GetActorsOfClassInView(AActor::StaticClass());
}

void AEnemyBase::BeginPlay() {
	Super::BeginPlay();
}

void AEnemyBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	//TArray<FActorSignalPair> a = GetVisibleActors();
	//GEngine->AddOnScreenDebugMessage(18095, 0.1f, FColor::Black,
	//	FString::Printf(TEXT("Player Detection Delta: %f"), dr));
}

void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

