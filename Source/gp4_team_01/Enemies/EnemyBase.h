#pragma once

#include "CoreMinimal.h"
#include "EnemyState.h"
#include "GameFramework/Character.h"
#include "gp4_team_01/Enviroment/Petrifiable.h"
#include "EnemyBase.generated.h"

enum EEnemyState : uint8;
class UWaypointHolderComponent;
class AEnemyAIController;
class APlayerCharacter;
class UWaypointComponent;
class UHearingComponent;
class USightComponent;
struct FPropertyChangedEvent;

UCLASS(Abstract)
class GP4_TEAM_01_API AEnemyBase : public ACharacter, public IPetrifiable
{
	GENERATED_BODY()

public:
	AEnemyBase();

	FORCEINLINE void RegisterSight(USightComponent* Component) { SightComponents.AddUnique(Component); }

	FORCEINLINE void RegisterHearing(UHearingComponent* Component) {
		if(!HearingComponent)
			HearingComponent = Component;
	}

	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(DefaultToSelf=Target), Category = "AI|Perception")
		static bool IsActorInView(AEnemyBase* Target, AActor* Actor, float& SignalStrength);
	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(DefaultToSelf=Target), Category = "AI|Perception")
		static bool IsLocationInView(AEnemyBase* Target, FVector Location, float Tolerance, float& SignalStrength);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(DefaultToSelf=Target),  Category = "AI|Perception") 
		static struct FPerceptionSignal GetVisionSignalToPlayer(AEnemyBase* Target);
	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(DefaultToSelf=Target), Category = "AI|Perception") 
		static TArray<struct FPerceptionSignal> GetVisionSignalsOfClass(AEnemyBase* Target, TSubclassOf<AActor> Class);
	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(DefaultToSelf=Target), Category = "AI|Perception") 
		static TArray<struct FPerceptionSignal> GetVisionSignals(AEnemyBase* Target);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(DefaultToSelf=Target), Category = "AI|Perception") 
		static FPerceptionSignal GetLastHearingSignal(AEnemyBase* Target);
	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(DefaultToSelf=Target), Category = "AI|Perception") 
		static bool HasNewSignalBeenHeard(AEnemyBase* Target);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AI|State")
		EEnemyState GetCurrentState() const { return CurrentState; }

	UFUNCTION(BlueprintCallable, Category = "AI|State")
		void SetCurrentState(const TEnumAsByte<EEnemyState> NewState) { CurrentState = NewState; }
	
	UFUNCTION(BlueprintCallable)
		bool Petrify(UObject* Target, APlayerCharacter* Player) override;
	UFUNCTION(BlueprintCallable)
		void Unpetrify(UObject* Target, APlayerCharacter* Player) override;
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
		FORCEINLINE bool GetIsPetrified() const noexcept { return bIsPetrified; }

	UFUNCTION(BlueprintCallable)
		void OnDeath(const AActor* Killer);
	
	UHearingComponent* GetHearingComponent() const { return HearingComponent; };

	UFUNCTION(BlueprintCallable)
	FVector GetNextWaypointLocation();
protected:
	TArray<AActor*> GetVisibleActorCandidatesOfClass(TSubclassOf<AActor> Class) const;
	TArray<AActor*> GetVisibleActorCandidates() const;
	
	virtual void BeginPlay() override;

private:	//EDITOR ONLY functions
	UFUNCTION(CallInEditor, Category = "Waypoints")
		void UpdateNavigationArrays() const;

	UFUNCTION(CallInEditor, Category = "Waypoints")
		void DeleteAllWaypoints() const;
	virtual bool ShouldTickIfViewportsOnly() const override { return true; };
public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
protected:
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	//	TObjectPtr<class UBehaviorTree> BehaviorTreeAsset;

	bool bIsPetrified = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Waypoints")
		int NumberOfIdleWaypoints;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Waypoints")
		UWaypointHolderComponent* IdleWaypointHolder;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Waypoints")
		int NumberOfSuspiciousWaypoints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Waypoints")
		UWaypointHolderComponent* SuspiciousWaypointHolder;
	
	UPROPERTY()
		TArray<USightComponent*> SightComponents;

	UPROPERTY()
		UHearingComponent* HearingComponent;

	UPROPERTY(EditInstanceOnly)
		AActor* DebugActor;

	UPROPERTY(VisibleAnywhere, Category = "Debug")
		TEnumAsByte<EEnemyState> CurrentState;

	AEnemyAIController* EnemyController;
};


