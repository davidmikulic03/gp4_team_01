﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "gp4_team_01/Enviroment/Interactable.h"
#include "PlayerCharacter.h"
#include "Pickup.generated.h"

class APlayerCharacter;

UCLASS()
class GP4_TEAM_01_API APickup : public AInteractable
{
	GENERATED_BODY()

public:
	APickup();
	virtual void Tick(float DeltaTime) override;
	
	virtual void Interact(AActor* Caller) override;
	inline ItemType GetItemType() const { return ItemType; };
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere, Category="Pickup")
	int AmountToAdd = 5;
	UPROPERTY(EditAnywhere, Category="Pickup")
	ItemType ItemType;
};
