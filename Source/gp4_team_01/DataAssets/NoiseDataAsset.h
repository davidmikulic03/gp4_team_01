﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NoiseDataAsset.generated.h"

class UFMODEvent;

UCLASS()
class GP4_TEAM_01_API UNoiseDataAsset : public UPrimaryDataAsset {
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "General")
	FName Name = "Noise Event";
	UPROPERTY(EditDefaultsOnly, Category = "SFX")
	UFMODEvent* Sound;
	//TODO: add more seetings for sound (volume, attenuation that maybe is proportional to intensity, etc)
	UPROPERTY(EditDefaultsOnly, Category = "Noise")
	bool bCanAlertAI = false;

	//TODO: add radius? Radius can be just proportional to intensity
	UPROPERTY(EditDefaultsOnly, Category = "Noise", meta = (EditCondition = "bCanAlertAI", EditConditionHides))
	float Intensity;

	UPROPERTY(EditDefaultsOnly, Category = "Noise")
	bool bSpecifyCustomRadius;

	UPROPERTY(EditDefaultsOnly, Category = "Noise", meta = (EditCondition = "bSpecifyCustomRadius", EditConditionHides))
	float Radius;
};
