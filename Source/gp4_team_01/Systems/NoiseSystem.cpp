#include "NoiseSystem.h"

#include "gp4_team_01/DataAssets/NoiseDataAsset.h"
#include "gp4_team_01/Enemies/AI/HearingComponent.h"
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

void ANoiseSystem::PlaySFX(const UNoiseDataAsset* NoiseDataAsset, const FVector& Location, bool bPickRandom) const {
	if(NoiseDataAsset->Sounds.IsEmpty()) {
		UE_LOG(LogTemp, Error, TEXT("ERROR: Couldn't play sound, missing ref in NoiseDataAsset"));
		return;
	}
	int RandomSoundId = NoiseDataAsset->Sounds.Num() > 1 ? FMath::RandRange(0, NoiseDataAsset->Sounds.Num() - 1) : 0;
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), NoiseDataAsset->Sounds[RandomSoundId], Location);

	//if (IFMODStudioModule::IsAvailable())
	//{
	//	FMOD::Studio::System* StudioSystem = IFMODStudioModule::Get().GetStudioSystem(EFMODSystemContext::Runtime);
	//	if (StudioSystem)
	//	{
	//		// Use it here
	//	}
	//}
}

