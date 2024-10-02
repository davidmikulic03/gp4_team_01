#include "SightComponent.h"
#include "EnemyBase.h"
#include "SceneRenderTargetParameters.h"
#include "kismet/KismetSystemLibrary.h"

USightComponent::USightComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	OnComponentBeginOverlap.AddDynamic(this, &ThisClass::BeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &ThisClass::EndOverlap);
	SetHiddenInGame(true);
	SetDefaultCollisionResponse();
	UpdateVisionMeshScale();
}

bool USightComponent::IsActorVisible(AActor* Actor, float& ModifiedDetectionRate) {
	ModifiedDetectionRate = 0.f;
	if (!Actor || !ActorsInVisionCone.Contains(Actor))
		return false;
	//FVector ToActor = Actor->GetActorLocation();
	//auto cosAngle = GetForwardVector().Dot(ToActor.GetSafeNormal());
	//if(cosAngle < FMath::Cos(ViewAngle))
	//	return false;

	FHitResult Hit;
	TArray<AActor*> ignores;
	ignores.Init(GetOwner(), 1);

	UKismetSystemLibrary::LineTraceSingle(GetWorld(), GetComponentLocation(), Actor->GetActorLocation(),
	                                      UEngineTypes::ConvertToTraceType(TraceChannel), false, ignores,
	                                      EDrawDebugTrace::None, Hit, true);
	//GetWorld()->LineTraceSingleByChannel(Hit, GetComponentLocation(), Actor->GetActorLocation(), TraceChannel);

	if(Hit.GetActor()) {
		FColor DebugDrawColor = FColor::Red;
		if (Hit.GetActor() == Actor) {
			ModifiedDetectionRate = DetectionRate;
			if(DetectionFalloffPower != 0)
				ModifiedDetectionRate /= FMath::Pow(Hit.Distance / 100, DetectionFalloffPower);
			DebugDrawColor = FColor::Green;
		}
		DrawDebugLine(GetWorld(), GetComponentLocation(), Hit.Location, DebugDrawColor);
		DrawDebugPoint(GetWorld(), Hit.Location, 10.f, DebugDrawColor);
		return true;
	}
	else return false;
}

TArray<AActor*> USightComponent::GetAllVisibleActors() {
	TArray<AActor*> Result;
	Result.Reserve(ActorsInVisionCone.Num());
	for (auto a : ActorsInVisionCone) {
		float discard;
		if(IsActorVisible(a, discard))
			Result.Add(a);
	}
	return Result;
}

void USightComponent::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
                                   const FHitResult& SweepResult)
{
	if (OtherActor == GetOwner())
		return;
	ActorsInVisionCone.AddUnique(OtherActor);
}

void USightComponent::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	if (ActorsInVisionCone.Contains(OtherActor))
		ActorsInVisionCone.Remove(OtherActor);
}


void USightComponent::BeginPlay()
{
	Super::BeginPlay();
	UpdateVisionMeshScale();
	auto OwningAI = Cast<AEnemyBase>(GetOwner());
	if (OwningAI)
		OwningAI->RegisterSight(this);
}

void USightComponent::UpdateVisionMeshScale() {
	float width = FMath::Tan(FMath::DegreesToRadians(ViewAngle));
	SetRelativeScale3D(0.01 * ViewDistance * FVector(1.0, width, width));
}

void USightComponent::SetDefaultCollisionResponse()
{
	SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SetCollisionResponseToAllChannels(ECR_Ignore);
	SetCollisionResponseToChannel(TraceChannel, ECR_Overlap);
	SetCollisionObjectType(ECC_WorldDynamic);

	CanCharacterStepUpOn = ECB_No;
}

#if WITH_EDITOR
void USightComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	UpdateVisionMeshScale();
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif
