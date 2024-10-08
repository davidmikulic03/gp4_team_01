// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "gp4_team_01/Enviroment/Interactable.h"
#include "gp4_team_01/Public/CPlayerCharacter.h"
#include "Pickup.generated.h"

class ACPlayerCharacter;

UCLASS()
class GP4_TEAM_01_API APickup : public AInteractable
{
	GENERATED_BODY()

public:
	APickup();
	virtual void Tick(float DeltaTime) override;
	virtual void Interact(AActor* Caller) override;
	bool GetIsThrowable();
protected:
	virtual void BeginPlay() override;
private:

//variables
public:
protected:
private:
	UPROPERTY(EditAnywhere, Category="Pickup")
	int AmountToAdd = 5; //TEST
	UPROPERTY(EditAnywhere, Category="Pickup")
	bool bIsThrowable = false;

	UPROPERTY(EditAnywhere, Category="Pickup")
	bool bIsHealth; //change it later. This is left vague and simple for explansion
};
