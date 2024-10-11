// Fill out your copyright notice in the Description page of Project Settings.


#include "Petrifiable.h"
#include "gp4_team_01/Player/PlayerCharacter.h"


// Add default functionality here for any IPetrifiable functions that are not pure virtual.
bool IPetrifiable::Petrify(UObject* Target, APlayerCharacter* Player) {
	Execute_OnPetrify(Target, Player);
	if(GEngine && Player)
		GEngine->AddOnScreenDebugMessage(666, 15.f, FColor::Blue,
			FString::Printf(TEXT("%s petrified by %s"), *Target->GetName(), *Player->GetName()));
	return true;
}

void IPetrifiable::Unpetrify(UObject* Target, APlayerCharacter* Player) {
	Execute_OnUnpetrify(Target, Player);
	if(GEngine && Player)
		GEngine->AddOnScreenDebugMessage(666, 15.f, FColor::Green,
			FString::Printf(TEXT("%s unpetrified by %s"),*Target->GetName(), *Player->GetName()));
}
