#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "gp4_team_01/Enemies/HearingComponent.h"
#include "NoiseSystem.generated.h"

class UHearingComponent;
class UNoiseDataAsset;

//TODO: gamemode should create this, hold a ref to it and make sure that it's a singleton
UCLASS(Abstract)
class GP4_TEAM_01_API ANoiseSystem : public AActor {
	GENERATED_BODY()

public:
	ANoiseSystem();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void RegisterListener(UHearingComponent* Listener) { Listeners.Add(Listener); };

	UFUNCTION(BlueprintCallable)
	void RegisterNoiseEvent(const UNoiseDataAsset* NoiseDataAsset, const FVector& Location);
	
private:
	void DispatchNoiseEvent(const UNoiseDataAsset* NoiseDataAsset, const FVector& Location);
	void PlaySFX(const UNoiseDataAsset* NoiseDataAsset, const FVector& Location) const;
	
private:
	UPROPERTY()
	TArray<UHearingComponent*> Listeners;
};
