﻿#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Magnet.generated.h"

UCLASS()
class GP4_TEAM_01_API AMagnet : public AActor
{
	GENERATED_BODY()

public:
	AMagnet();

	UPROPERTY(EditAnywhere)
		USceneComponent* TraversalTarget;

	UPROPERTY(EditAnywhere)
		USceneComponent* AimTarget;
protected:
	virtual void BeginPlay() override;

};