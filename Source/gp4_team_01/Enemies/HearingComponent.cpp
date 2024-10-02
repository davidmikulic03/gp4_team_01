

#include "HearingComponent.h"

#include "gp4_team_01/DataAssets/NoiseDataAsset.h"
#include "gp4_team_01/Systems/MainGameMode.h"
#include "gp4_team_01/Systems/NoiseSystem.h"
#include "Kismet/GameplayStatics.h"


UHearingComponent::UHearingComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}


void UHearingComponent::BeginPlay() {
	Super::BeginPlay();

	ANoiseSystem* NoiseSystemRef = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->GetNoiseSystemRef();
	NoiseSystemRef->RegisterListener(this);
}

void UHearingComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHearingComponent::OnNoiseHeard(const UNoiseDataAsset* NoiseDataAsset, const FVector& Location) {
	//TODO: Add logic for NoiseDataAsset with bSpecifyCustomRadius == false
	if(NoiseDataAsset->bSpecifyCustomRadius) {
		
		DrawDebugSphere(GetWorld(), Location, NoiseDataAsset->Radius, 20, FColor::Purple, false, 1);
		if((GetOwner()->GetActorLocation() - Location).Length() < NoiseDataAsset->Radius) {
			UE_LOG(LogTemp, Warning, TEXT("Heard noise with intesity %f at location %s"), NoiseDataAsset->Intensity, *Location.ToString());
			CurrentDetection += NoiseDataAsset->Intensity;
			if(CurrentDetection >= DetectionThreshold) {
				//TODO: detection logic that can be read by the BT.
			}
		}
	}
}

