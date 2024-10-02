#include "NoiseSystem.h"

#include "gp4_team_01/DataAssets/NoiseDataAsset.h"
#include "gp4_team_01/Enemies/HearingComponent.h"
#include "Kismet/GameplayStatics.h"


ANoiseSystem::ANoiseSystem() {
	PrimaryActorTick.bCanEverTick = true;
}

void ANoiseSystem::BeginPlay() {
	Super::BeginPlay();
	
}

void ANoiseSystem::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void ANoiseSystem::RegisterNoiseEvent(const UNoiseDataAsset* NoiseDataAsset, const FVector& Location) {
	PlaySFX(NoiseDataAsset, Location);
	if(NoiseDataAsset->bCanAlertAI)
			DispatchNoiseEvent(NoiseDataAsset, Location);
}

void ANoiseSystem::DispatchNoiseEvent(const UNoiseDataAsset* NoiseDataAsset, const FVector& Location) {
	for (const auto& Listener : Listeners) {
		Listener->OnNoiseHeard(NoiseDataAsset, Location);
	}
}

void ANoiseSystem::PlaySFX(const UNoiseDataAsset* NoiseDataAsset, const FVector& Location) const {
	if(!NoiseDataAsset->Sound) {
		UE_LOG(LogTemp, Error, TEXT("ERROR: Couldn't play sound, missing ref in NoiseDataAsset"));
		return;
	}
	
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), NoiseDataAsset->Sound, Location);
}

