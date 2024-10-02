#pragma once

#include "CoreMinimal.h"
#include "PerceptionSignal.generated.h"

USTRUCT(BlueprintType)
struct FPerceptionSignal {
	GENERATED_BODY()

	FPerceptionSignal() { Actor = nullptr; SignalStrength = 0.f; OverrideOrigin = FVector::ZeroVector; }
	FPerceptionSignal(float SignalStrength, AActor* Actor)
		:  SignalStrength(SignalStrength), Actor(Actor) { }
	FPerceptionSignal(float SignalStrength, FVector Origin)
		:  SignalStrength(SignalStrength), OverrideOrigin(Origin) { }

	
	float SignalStrength;
	AActor* Actor = nullptr;
	FVector OverrideOrigin;
};

UCLASS()
class USignalFunctions : public UObject {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="AI|Perception")
		static FVector GetSignalOrigin(FPerceptionSignal Signal) noexcept {
		return Signal.Actor ? Signal.Actor->GetActorLocation() : Signal.OverrideOrigin;
	}
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="AI|Perception")
		static AActor* GetActor(FPerceptionSignal Signal) noexcept { return Signal.Actor; }
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="AI|Perception")
		static float GetSignalStrength(FPerceptionSignal Signal) noexcept { return Signal.SignalStrength; }
};

