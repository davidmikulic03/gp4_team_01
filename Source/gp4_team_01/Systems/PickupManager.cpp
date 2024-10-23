#include "PickupManager.h"

#include "gp4_team_01/Player/Pickup.h"


void UPickupManager::SavePickupStates() {
	for(int i = 0; i < Pickups.Num(); i++) {
		if(i == PickupStates.Num())
			PickupStates.Add(Pickups[i]->GetEnabled());
		else if(i > PickupStates.Num())
			break;
		else PickupStates[i] = Pickups[i]->GetEnabled();
	}
}

void UPickupManager::LoadPickupStates() {
	for(int i = 0; i < Pickups.Num(); i++) {
		if(i < PickupStates.Num()) {
			Pickups[i]->SetEnabled(PickupStates[i]);
		}
		else break;
	}
}

void UPickupManager::Register(APickup* Pickup) {
	Pickups.Add(Pickup);
	PickupStates.Add(Pickup->GetEnabled());
}
