// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/MeshComponent.h"
#include "SightComponent.generated.h"


UCLASS(ClassGroup=(AI), meta=(BlueprintSpawnableComponent))
class GP4_TEAM_01_API USightComponent : public UStaticMeshComponent {
	GENERATED_BODY()
public:
	USightComponent();

	bool IsActorVisible(AActor* Actor, float& ModifiedDetectionRate);
	TArray<AActor*> GetAllVisibleActors();

	FORCEINLINE TArray<AActor*> GetActorsInVisionCone() { return ActorsInVisionCone; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Perception)
		float DetectionRate = 1.0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Perception)
		float DetectionFalloffPower = 0.0;

protected:
	virtual void BeginPlay() override;
	virtual void UpdateVisionMeshScale();
	void SetDefaultCollisionResponse();
	
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, 
					  AActor* OtherActor, 
					  UPrimitiveComponent* OtherComponent, 
					  int32 OtherBodyIndex, 
					  bool bFromSweep, 
					  const FHitResult &SweepResult );
	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, 
					  AActor* OtherActor, 
					  UPrimitiveComponent* OtherComponent, 
					  int32 OtherBodyIndex);
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	UPROPERTY(EditDefaultsOnly, Category = Perception)
		float ViewDistance = 1000.f;
	UPROPERTY(EditDefaultsOnly, Category = Perception, meta = (UIMin = 0.f, UIMax = 89.9f));
		float ViewAngle = 45.f;
	
	UPROPERTY(EditDefaultsOnly, Category = Perception)
		TEnumAsByte<ECollisionChannel> TraceChannel = ECC_GameTraceChannel1;

	TArray<AActor*> ActorsInVisionCone;
};
