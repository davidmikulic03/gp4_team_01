#pragma once

#include "CoreMinimal.h"
#include "ActorSignalPair.generated.h"

USTRUCT(BlueprintType)
struct FActorSignalPair {
	GENERATED_BODY()

	FActorSignalPair() { Actor = nullptr; DetectionRate = 0.f; }
	FActorSignalPair(AActor* Actor, float DetectionRate)
		:  Actor(Actor), DetectionRate(DetectionRate) { }

	UPROPERTY(BlueprintReadOnly)
	AActor* Actor;
	UPROPERTY(BlueprintReadOnly)
	float DetectionRate;
};