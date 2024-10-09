#include "MagnetComponent.h"

#include "CPlayerCharacter.h"
#include "gp4_team_01/Enviroment/Magnet.h"

UMagnetComponent::UMagnetComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}

bool UMagnetComponent::Use() {
	if(InteractableMagnets.IsEmpty())
		return false;
	TraversalCounter = 0.f;
	TraversalStart = GetOwner()->GetActorLocation();
	bIsTraversing = true;
	return true;
}

void UMagnetComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction) {
	if(!bIsTraversing)
		RegenerateInteractableArray();
	else {
		Traverse(DeltaTime);
	}
	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UMagnetComponent::RegenerateInteractableArray() {
	InteractableMagnets.Empty();
	auto Player = Cast<ACPlayerCharacter>(GetOwner());
	if(InInteractionRange.IsEmpty() || !Player) {
		return;
	}
	for (auto Magnet : InInteractionRange) {
		FVector ToMagnet = Magnet->AimTarget->GetComponentLocation() - GetOwner()->GetActorLocation();
		FVector ToMagnetDir = ToMagnet.GetSafeNormal();
		float dot = ToMagnetDir.Dot(Player->GetCamera()->GetForwardVector());
		if(dot > FMath::Cos(FMath::DegreesToRadians(AimThreshold))) {
			InteractableMagnets.Add(Magnet);
		}
	}
}

float UMagnetComponent::ModifyInterpolation(float Alpha) { return Alpha * Alpha; }

void UMagnetComponent::BeginPlay() {
	Super::BeginPlay();

}

void UMagnetComponent::Traverse(double DeltaTime) {
	float alpha = ModifyInterpolation(TraversalCounter / TraversalTime);
	GetOwner()->SetActorLocation(FMath::Lerp(
		TraversalStart, InteractableMagnets[0]->TraversalTarget->GetComponentLocation(), alpha));
	TraversalCounter+= DeltaTime;
	if(TraversalCounter >= TraversalTime) {
		bIsTraversing = false;
		TraversalCounter = 0;
		if(auto Player = Cast<ACPlayerCharacter>(GetOwner()))
			Player->GetCapsuleComponent()->SetPhysicsLinearVelocity(FVector::Zero());
	}
}

void UMagnetComponent::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor) {
	if(auto a = Cast<AMagnet>(OtherActor)) {
		InInteractionRange.AddUnique(a);
	}
}

void UMagnetComponent::EndOverlap(AActor* OverlappedActor, AActor* OtherActor) {
	if(auto a = Cast<AMagnet>(OtherActor)) {
		InInteractionRange.Remove(a);
	}
}

