#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

class UHearingComponent;
class USightComponent;
struct FPropertyChangedEvent;

UCLASS(Abstract)
class GP4_TEAM_01_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyBase();
	// TODO: Change APawn* to Player Class.
	UFUNCTION(BlueprintCallable)
	virtual void Petrify(APawn* Player);
	UFUNCTION(BlueprintCallable)
	virtual void Unpetrify(APawn* Player);

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
	
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
		FORCEINLINE bool GetIsPetrified() const noexcept { return bIsPetrified; }

	UFUNCTION(BlueprintCallable)
		void OnDeath(const AActor* Killer);
	
	UHearingComponent* GetHearingComponent() const { return HearingComponent; };
	
protected:
	UFUNCTION(BlueprintImplementableEvent)
		void OnPetrify(APawn* Player);
	UFUNCTION(BlueprintImplementableEvent)
		void OnUnpetrify(APawn* Player);
	
	TArray<AActor*> GetVisibleActorCandidatesOfClass(TSubclassOf<AActor> Class) const;
	TArray<AActor*> GetVisibleActorCandidates() const;
	
	virtual void BeginPlay() override;

private:	//EDITOR ONLY functions
	UFUNCTION(CallInEditor, Category = "Pathfinding")
		void UpdateNavigationArrays();

	UFUNCTION(CallInEditor, Category = "Pathfinding")
		void DeleteAllWaypoints();

	UFUNCTION(CallInEditor, Category = "Pathfinding")
	void DrawPath();
	
	void DrawPath_Internal(bool bPersistantLines = false);

	virtual void PostEditChangeProperty(FPropertyChangedEvent& FPropertyChangedEvent) override;
	//virtual bool ShouldTickIfViewportsOnly() const override { return true; };

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
protected:
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	//	TObjectPtr<class UBehaviorTree> BehaviorTreeAsset;

	bool bIsPetrified = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pathfinding")
		int NumberOfIdleWaypoints;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pathfinding")
		TArray<USceneComponent*> IdleWaypoints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pathfinding")
		int NumberOfAlertWaypoints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pathfinding")
		TArray<USceneComponent*> AlertWaypoints;
	
	
	UPROPERTY()
		TArray<USightComponent*> SightComponents;

	UPROPERTY()
		UHearingComponent* HearingComponent;

	UPROPERTY(EditInstanceOnly)
		AActor* DebugActor;
};


