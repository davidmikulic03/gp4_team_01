// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Petrifiable.generated.h"

UINTERFACE()
class UPetrifiable : public UInterface
{
	GENERATED_BODY()
};

class GP4_TEAM_01_API IPetrifiable
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual bool Petrify(UObject* Target, APlayerCharacter* Player);
	UFUNCTION()
	virtual void Unpetrify(UObject* Target, APlayerCharacter* Player);

protected:
	//void Execute_OnPetrify(APlayerCharacter* Player) { OnPetrify(Player); }
	//void Execute_OnUnpetrify(APlayerCharacter* Player) { OnUnpetrify(Player); }
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnPetrify(APlayerCharacter* Player);
	UFUNCTION(BlueprintImplementableEvent)
	void OnUnpetrify(APlayerCharacter* Player);
};
