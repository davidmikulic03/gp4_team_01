#include "EnemyBase.h"

#include "AI/HearingComponent.h"
#include "AI/SightComponent.h"
#include "AI/PerceptionSignal.h"
#include "Components/CapsuleComponent.h"

#if WITH_EDITOR
#include "UnrealEdGlobals.h"
#include "Editor/UnrealEdEngine.h"
#endif

#include "gp4_team_01/Utility/WaypointComponent.h"
#include "Kismet/GameplayStatics.h"


AEnemyBase::AEnemyBase() {
	PrimaryActorTick.bCanEverTick = true;

	WaypointHolder = CreateDefaultSubobject<USceneComponent>("Waypoint Holder");
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
	CurrentWaypointIndex += 1;
	if(CurrentWaypointIndex >= IdleWaypoints.Num())
		CurrentWaypointIndex = 0;
	
	return IdleWaypoints[CurrentWaypointIndex]->GetComponentLocation();
}

void AEnemyBase::BeginPlay() {
	Super::BeginPlay();

	CurrentWaypointIndex = 0;
}

void AEnemyBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

#if WITH_EDITOR
	DrawPath_Internal(false);
#endif
	
	//TArray<FActorSignalPair> a = GetVisibleActors();
	//GEngine->AddOnScreenDebugMessage(18095, 0.1f, FColor::Black,
	//	FString::Printf(TEXT("Player Detection Delta: %f"), dr));
}

void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


#if WITH_EDITOR
void AEnemyBase::UpdateNavigationArrays() {
	for(int i = IdleWaypoints.Num(); i < NumberOfIdleWaypoints; i++) {
		UWaypointComponent* NewWaypoint = NewObject<UWaypointComponent>(this, FName("Waypoint"));
		NewWaypoint->SetWorldLocation(GetActorLocation());
		NewWaypoint->SetupAttachment(WaypointHolder);
		this->AddInstanceComponent(NewWaypoint);
		this->AddOwnedComponent(NewWaypoint);
		NewWaypoint->RegisterComponent();
		IdleWaypoints.Add(NewWaypoint);
	}
}

void AEnemyBase::DeleteAllWaypoints() {
	for(int i = 0; i < IdleWaypoints.Num(); i++) {
		IdleWaypoints[i]->DestroyComponent();
	}
	IdleWaypoints.Empty();
}

void AEnemyBase::DrawPath() {
	DrawPath_Internal(true);
}

void AEnemyBase::DrawPath_Internal(bool bPersistantLines) {
	for(int i = 0; i < IdleWaypoints.Num() - 1; i++) {
		DrawDebugLine(GetWorld(), IdleWaypoints[i]->GetComponentLocation(), IdleWaypoints[i+1]->GetComponentLocation(), FColor::Purple, bPersistantLines, -1, 0, 10);
	}
	if(IdleWaypoints.Num() >= 2)
		DrawDebugLine(GetWorld(), IdleWaypoints[IdleWaypoints.Num() - 1]->GetComponentLocation(), IdleWaypoints[0]->GetComponentLocation(), FColor::Purple, bPersistantLines, -1, 0, 10);
}

void AEnemyBase::PostEditChangeProperty(FPropertyChangedEvent& FPropertyChangedEvent) {
	Super::PostEditChangeProperty(FPropertyChangedEvent);
	//GUnrealEd->UpdateFloatingPropertyWindows();
}
#endif
