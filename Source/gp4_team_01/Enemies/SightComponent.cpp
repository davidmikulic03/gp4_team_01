#include "SightComponent.h"
#include "GameFramework/Character.h"
#include "EnemyBase.h"

USightComponent::USightComponent() {
	PrimaryComponentTick.bCanEverTick = false;
	OnComponentBeginOverlap.AddDynamic(this, &ThisClass::BeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &ThisClass::EndOverlap);
	SetHiddenInGame(true);
	UpdateVisionMeshScale();
}

bool USightComponent::IsPlayerVisible() {
	if(!Player)
		return false;

	FHitResult Hit;
	GetWorld()->LineTraceSingleByChannel(Hit, GetComponentLocation(), Player->GetActorLocation(), TraceChannel);
	if(Hit.GetActor() && Cast<ACharacter>(Hit.GetActor()))
		return true;
	else
		return false;
}

void USightComponent::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	auto asPlayer = Cast<ACharacter>(OtherComponent->GetOwner());
	if(asPlayer && asPlayer != GetOwner())
		Player = asPlayer;
}

void USightComponent::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex) {
	auto asPlayer = Cast<ACharacter>(OtherActor);
	if(asPlayer && asPlayer != GetOwner())
		Player = nullptr;
}


void USightComponent::BeginPlay() {
	Super::BeginPlay();
	UpdateVisionMeshScale();
	auto OwningAI = Cast<AEnemyBase>(GetOwner());
	if(OwningAI)
		OwningAI->RegisterSight(this);
}

void USightComponent::UpdateVisionMeshScale() {
	float width = FMath::Tan(FMath::DegreesToRadians(ViewAngle));
	SetRelativeScale3D(0.01 * ViewDistance * FVector(1.0, width, width));
}

#if WITH_EDITOR
void USightComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {
	UpdateVisionMeshScale();
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif
