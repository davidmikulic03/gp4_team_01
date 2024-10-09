#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MagnetComponent.generated.h"


class AMagnet;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GP4_TEAM_01_API UMagnetComponent : public UActorComponent {
	GENERATED_BODY()

public:
	UMagnetComponent();

	bool Use();

	FORCEINLINE bool IsTraversing() const noexcept { return bIsTraversing; } 
	
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION()
		void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
		void EndOverlap(AActor* OverlappedActor, AActor* OtherActor);
protected:
	virtual void BeginPlay() override;
	void Traverse(double DeltaTime);
	void RegenerateInteractableArray();

	float ModifyInterpolation(float Alpha);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Magnet, meta=(UIMin=0,UIMax=180))
		float AimThreshold = 60;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Magnet)
		float TraversalTime = 0.5f;
	float TraversalCounter = 0;
	bool bIsTraversing = false;
	FVector TraversalStart;
	
	TArray<AMagnet*> InInteractionRange;
	TArray<AMagnet*> InteractableMagnets;
};
