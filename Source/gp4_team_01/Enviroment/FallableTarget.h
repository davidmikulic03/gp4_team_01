// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableTargetDoor.h"
#include "FallableTarget.generated.h"

class AEnemyBase;

UCLASS()
class GP4_TEAM_01_API AFallableTarget : public AInteractableTargetDoor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFallableTarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnInteract() override;
	virtual void OnUnInteract() override { UE_LOG(LogTemp, Error, TEXT("This is a fallable, it should NOT have OnUnInteract called on it")); };

	UFUNCTION(BlueprintImplementableEvent)
	void FallableBreakEvent();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	
	virtual void OnBreak();

private:
	UPROPERTY(EditAnywhere, Category = "Fallable")
	bool bKillsEnemyOnFall = false;

	UPROPERTY(EditInstanceOnly, Category = "Fallable", meta = (EditCondition = "bKillsEnemyOnFall", EditConditionHides))
	AEnemyBase* EnemyToKill = nullptr;

};
