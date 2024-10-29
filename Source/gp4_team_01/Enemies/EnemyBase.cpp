#include "EnemyBase.h"

#include "AI/HearingComponent.h"
#include "AI/SightComponent.h"
#include "AI/PerceptionSignal.h"
#include "Components/CapsuleComponent.h"
#include "gp4_team_01/Utility/WaypointComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AI/EnemyAIController.h"
#include "AI/FuzzyBrainComponent.h"

#if WITH_EDITOR
#include "UnrealEdGlobals.h"
#include "Editor/UnrealEdEngine.h"
#endif

#include "EnemyManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "gp4_team_01/Systems/MainGameMode.h"
#include "gp4_team_01/Systems/NoiseSystem.h"
#include "gp4_team_01/Utility/WaypointHolderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"


AEnemyBase::AEnemyBase() {
	PrimaryActorTick.bCanEverTick = true;
	
	IdleWaypointHolder = CreateDefaultSubobject<UWaypointHolderComponent>("Idle Waypoint Holder");
	SuspiciousWaypointHolder = CreateDefaultSubobject<UWaypointHolderComponent>("Alert Waypoint Holder");
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

void AEnemyBase::SaveState() {
	TEnumAsByte<EEnemyState> State = CurrentState != static_cast<TEnumAsByte<EEnemyState>>(Agitated)
		? CurrentState : static_cast<TEnumAsByte<EEnemyState>>(Suspicious);
	Save = FCheckpointSave{ GetActorTransform(), State };
}

void AEnemyBase::LoadState() {
	//SetActorTransform(Save.Transform);
	SetCurrentState(Save.State);
	//SetActorTransform(Save.Transform);
	//GetNextWaypointLocation();

	if(EnemyController->GetBlackboardComponent()) {
		EnemyController->GetBlackboardComponent()->Deactivate();
		EnemyController->GetBlackboardComponent()->Activate();
	}
	
	EnemyController->Reset();
}

UFuzzyBrainComponent* AEnemyBase::GetBrain() const {
	if(EnemyController)
		return EnemyController->Brain;
	else
		return nullptr;
}

bool AEnemyBase::Petrify(UObject* Target, APlayerCharacter* Player) {
	bIsPetrified = true;
	EnemyController->Brain->SetIsThinking(false);
	return IPetrifiable::Petrify(Target, Player);
}

void AEnemyBase::Unpetrify(UObject* Target, APlayerCharacter* Player) {
	if(!Target)
		return;
	bIsPetrified = false;
	EnemyController->Brain->SetIsThinking(true);
	IPetrifiable::Unpetrify(Target, Player);
}

void AEnemyBase::Die(const AActor* Killer) {
	//TODO: handle death better
	if(auto g = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
		if(auto n = g->GetNoiseSystemRef())
			n->UnregisterListener(HearingComponent);
	OnDeath();
	
}

void AEnemyBase::OnDeath_Implementation() { Destroy(); }

FVector AEnemyBase::GetNextWaypointLocation()
{
	
	if(CurrentState == EEnemyState::Idle) {
		if(NumberOfIdleWaypoints > 0)
			return IdleWaypointHolder->GetNextWaypoint();
	}
	else if(CurrentState == EEnemyState::Suspicious) {
		if(NumberOfSuspiciousWaypoints > 0)
			return SuspiciousWaypointHolder->GetNextWaypoint();
	}

	return FVector::Zero();
}

void AEnemyBase::BeginPlay() {
	Super::BeginPlay();
	EnemyController = Cast<AEnemyAIController>(Controller);
 	BaseSpeed = GetCharacterMovement()->MaxWalkSpeed;
	auto GameMode = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if(GameMode && GameMode->GetEnemyManagerRef()) {
		EnemyManager = GameMode->GetEnemyManagerRef();
		EnemyManager->Register(this);
	}
	SaveState();
}

void AEnemyBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

#if WITH_EDITOR
	IdleWaypointHolder->DrawPath(false);
	SuspiciousWaypointHolder->DrawPath(false);
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
	SuspiciousWaypointHolder->UpdateWaypointArray(NumberOfSuspiciousWaypoints, "Alert");
}

void AEnemyBase::DeleteAllWaypoints() const {
	IdleWaypointHolder->DeleteAllWaypoints();
	SuspiciousWaypointHolder->DeleteAllWaypoints();
}
#endif
