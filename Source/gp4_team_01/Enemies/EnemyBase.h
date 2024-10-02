
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

	FORCEINLINE void RegisterSight(USightComponent* Component) {
		if(!SightComponents.Contains(Component))
			SightComponents.Add(Component);
	}

	UFUNCTION(BlueprintCallable, BlueprintPure,  Category = "AI|Vision")
		bool IsActorVisible(AActor* Actor, float& DetectionRate);
	UFUNCTION(BlueprintCallable, BlueprintPure,  Category = "AI|Vision") 
		bool IsPlayerVisible(float& SignalStrength);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AI|Vision") 
		TArray<struct FActorSignalPair> GetVisibleActorsOfClass(TSubclassOf<AActor> Class);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "AI|Vision") 
		TArray<struct FActorSignalPair> GetVisibleActors();
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
		FORCEINLINE bool GetIsPetrified() const noexcept { return bIsPetrified; }
	
protected:
	UFUNCTION(BlueprintImplementableEvent)
		void OnPetrify(APawn* Player);
	UFUNCTION(BlueprintImplementableEvent)
		void OnUnpetrify(APawn* Player);
	
	TArray<AActor*> GetVisibleActorCandidatesOfClass(TSubclassOf<AActor> Class);
	TArray<AActor*> GetVisibleActorCandidates();
	
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


