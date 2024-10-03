
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

class USightComponent;

UCLASS(Abstract)
class GP4_TEAM_01_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyBase();
	// TODO: Change APawn* to Player Class.
	virtual void Petrify(APawn* Player);
	virtual void Unpetrify(APawn* Player);

	FORCEINLINE void RegisterSight(USightComponent* Component) { SightComponents.AddUnique(Component); }

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
	
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
		FORCEINLINE bool GetIsPetrified() const noexcept { return bIsPetrified; }
	
protected:
	UFUNCTION(BlueprintImplementableEvent)
		void OnPetrify(APawn* Player);
	UFUNCTION(BlueprintImplementableEvent)
		void OnUnpetrify(APawn* Player);
	
	TArray<AActor*> GetVisibleActorCandidatesOfClass(TSubclassOf<AActor> Class) const;
	TArray<AActor*> GetVisibleActorCandidates() const;
	
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
protected:
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	//	TObjectPtr<class UBehaviorTree> BehaviorTreeAsset;

	bool bIsPetrified = false;

	UPROPERTY()
		TArray<USightComponent*> SightComponents;
	
	UPROPERTY(BlueprintReadOnly)
		float Suspicion = 0.0;

	UPROPERTY(EditInstanceOnly)
		AActor* DebugActor;
};


