// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

private:
	//TODO: detection falloff? GetDetectedNoisePoint something something
	UPROPERTY(EditDefaultsOnly, Category = "Noise", meta = (AllowPrivateAccess = true))
	float DetectionThreshold = 100.f;

	UPROPERTY(VisibleAnywhere, Category = "Debug")
	float CurrentDetection = 0.f;
};
