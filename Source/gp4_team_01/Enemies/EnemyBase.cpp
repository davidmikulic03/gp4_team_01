﻿#include "EnemyBase.h"

#include "AI/HearingComponent.h"
#include "AI/SightComponent.h"
#include "AI/PerceptionSignal.h"

#include "gp4_team_01/Utility/WaypointHolderComponent.h"
#include "Kismet/GameplayStatics.h"


AEnemyBase::AEnemyBase() {
	PrimaryActorTick.bCanEverTick = true;

	IdleWaypointHolder = CreateDefaultSubobject<UWaypointHolderComponent>("Idle Waypoint Holder");
	AlertWaypointHolder = CreateDefaultSubobject<UWaypointHolderComponent>("Alert Waypoint Holder");
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

bool AEnemyBase::IsActorInView(AEnemyBase* Target, AActor* Actor, float& SignalStrength) {
	SignalStrength = 0.f;
	for(auto SightComponent : Target->SightComponents) {
		float currentComponentDetectionRate;
		if(SightComponent->IsActorVisible(Actor, currentComponentDetectionRate)) {
			if(currentComponentDetectionRate > SignalStrength)
				SignalStrength = currentComponentDetectionRate;
		}
	}
	return SignalStrength > 0;
}

bool AEnemyBase::IsLocationInView(AEnemyBase* Target, FVector Location, float Tolerance, float& SignalStrength) {
	SignalStrength = 0.f;
	for(auto SightComponent : Target->SightComponents) {
		float currentComponentDetectionRate;
		if(SightComponent->IsLocationVisible(Location, Tolerance, currentComponentDetectionRate)) {
			if(currentComponentDetectionRate > SignalStrength)
				SignalStrength = currentComponentDetectionRate;
		}
	}
	return SignalStrength > 0;
}

TArray<AActor*> AEnemyBase::GetVisibleActorCandidates() const {
	return GetVisibleActorCandidatesOfClass(AActor::StaticClass());
}

TArray<AActor*> AEnemyBase::GetVisibleActorCandidatesOfClass(TSubclassOf<AActor> Class) const {
	TArray<AActor*> Candidates;
	for (auto SightComponent : SightComponents) {
		for (auto Candidate : SightComponent->GetActorsInVisionCone()) {
			if(Candidate->IsA(Class))
				Candidates.AddUnique(Candidate);
		}
	}
	return Candidates;
}

FPerceptionSignal AEnemyBase::GetVisionSignalToPlayer(AEnemyBase* Target) {
	AActor* Player = UGameplayStatics::GetPlayerController(Target->GetWorld(), 0)->GetPawn();
	float SignalStrength;
	if(IsActorInView(Target, Player, SignalStrength))
		return FPerceptionSignal(SignalStrength, Player);
	else return FPerceptionSignal();
}

TArray<FPerceptionSignal> AEnemyBase::GetVisionSignalsOfClass(AEnemyBase* Target, TSubclassOf<AActor> Class) {
	TArray<FPerceptionSignal> Result;
	for(auto Actor : Target->GetVisibleActorCandidatesOfClass(Class)) {
		float DetectionRate;
		if(IsActorInView(Target, Actor, DetectionRate))
			Result.Add(FPerceptionSignal(DetectionRate, Actor));
	}
	return Result;
}

TArray<FPerceptionSignal> AEnemyBase::GetVisionSignals(AEnemyBase* Target) {
	return GetVisionSignalsOfClass(Target, AActor::StaticClass());
}

FPerceptionSignal AEnemyBase::GetLastHearingSignal(AEnemyBase* Target) {
	return  Target->GetHearingComponent()->GetLastNoiseSignal();
}

bool AEnemyBase::HasNewSignalBeenHeard(AEnemyBase* Target) {
	return Target && Target->GetHearingComponent() && Target->GetHearingComponent()->HasNewSignalBeenHeard();
}

void AEnemyBase::OnDeath(const AActor* Killer) {
	//TODO: handle death better
	Destroy();
}

FVector AEnemyBase::GetNextWaypointLocation()
{
	//TODO: Logic to return the correct waypoints based on enemy state
	return IdleWaypointHolder->GetNextWaypoint();
}

void AEnemyBase::BeginPlay() {
	Super::BeginPlay();
}

void AEnemyBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

#if WITH_EDITOR
	IdleWaypointHolder->DrawPath(false);
	AlertWaypointHolder->DrawPath(false);
#endif
	
	//TArray<FActorSignalPair> a = GetVisibleActors();
	//GEngine->AddOnScreenDebugMessage(18095, 0.1f, FColor::Black,
	//	FString::Printf(TEXT("Player Detection Delta: %f"), dr));
}

void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


#if WITH_EDITOR
void AEnemyBase::UpdateNavigationArrays() const {
	IdleWaypointHolder->UpdateWaypointArray(NumberOfIdleWaypoints, "Idle");
	AlertWaypointHolder->UpdateWaypointArray(NumberOfAlertWaypoints, "Alert");
}

void AEnemyBase::DeleteAllWaypoints() const {
	IdleWaypointHolder->DeleteAllWaypoints();
	AlertWaypointHolder->DeleteAllWaypoints();
}
#endif
