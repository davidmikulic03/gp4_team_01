﻿#pragma once

#include "CoreMinimal.h"
#include "PerceptionSignal.h"
#include "Components/ActorComponent.h"
#include "HearingComponent.generated.h"


class UNoiseDataAsset;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GP4_TEAM_01_API UHearingComponent : public UActorComponent {
	GENERATED_BODY()

public:
	UHearingComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

	void OnNoiseHeard(const UNoiseDataAsset* NoiseDataAsset, const FVector& Location);

	FPerceptionSignal GetLastNoiseSignal();
	
	bool HasNewSignalBeenHeard() const { return !bHasLastNoiseSignalBeenConsumed; };

private:
	//currently there's no hearing detection threshold
	////TODO: detection falloff? GetDetectedNoisePoint something something
	//UPROPERTY(EditDefaultsOnly, Category = "Noise", meta = (AllowPrivateAccess = true))
	//float DetectionThreshold = 100.f;

	//debug variables
	UPROPERTY(VisibleAnywhere, Category = "Debug")
	float LastNoiseSignalIntesity = 0.f;

	UPROPERTY(VisibleAnywhere, Category = "Debug")
	FVector LastNoiseSignalLocation;

	UPROPERTY(VisibleAnywhere, Category = "Debug")
	bool bHasLastNoiseSignalBeenConsumed = false;

	FPerceptionSignal LastNoiseSignal;
};
