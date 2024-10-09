// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DetectionModifier.generated.h"


UCLASS(ClassGroup=(AI), meta=(BlueprintSpawnableComponent))
class GP4_TEAM_01_API UDetectionModifier : public UActorComponent {
	GENERATED_BODY()

public:
	UDetectionModifier();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = 0.f))
		float DefaultSignalModifier = 1.0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = 0.f))
		float SecondarySignalModifier = 0.5;
	
};
