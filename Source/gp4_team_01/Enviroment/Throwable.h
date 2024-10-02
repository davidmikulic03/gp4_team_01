#pragma once

#include "CoreMinimal.h"
#include <gp4_team_01/Enviroment/NoiseMaker.h>
#include "Throwable.generated.h"

class ANoiseSystem;

UCLASS()
class GP4_TEAM_01_API AThrowable : public AActor, public INoiseMaker {
	GENERATED_BODY()

public:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	AThrowable();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void GenerateNoise(UNoiseDataAsset* NoiseDataAsset, FVector Location) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Throwable")
	float ThrowForce = 5.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Throwable | Noise")
	UNoiseDataAsset* OnHitNoiseAsset = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* Mesh = nullptr;

	UPROPERTY()
	ANoiseSystem* NoiseSystemRef = nullptr;
};
