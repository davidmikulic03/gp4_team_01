#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "WaypointComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GP4_TEAM_01_API UWaypointComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UWaypointComponent();

	void SetColor(const FColor NewColor) { Color = NewColor;};

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
private:
	UPROPERTY()
	FColor Color = FColor::Purple;
};
