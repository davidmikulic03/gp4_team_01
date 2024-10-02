#include "Throwable.h"

#include "gp4_team_01/Systems/MainGameMode.h"
#include "gp4_team_01/Systems/NoiseSystem.h"
#include "Kismet/GameplayStatics.h"

AThrowable::AThrowable() {
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	Mesh->OnComponentHit.AddDynamic(this, &AThrowable::OnHit);
}

void AThrowable::BeginPlay() {
	Super::BeginPlay();

	NoiseSystemRef = Cast<AMainGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->GetNoiseSystemRef();
}

void AThrowable::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AThrowable::GenerateNoise(UNoiseDataAsset* NoiseDataAsset, FVector Location) {
	NoiseSystemRef->RegisterNoiseEvent(NoiseDataAsset, Location);
}

void AThrowable::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit) {
	if(OnHitNoiseAsset && (GetVelocity().Length() >= 50)) //TODO: the hardcoded 10 is just to make sure it doesn't keep making noise with every microbounce, let's get rid of this
		GenerateNoise(OnHitNoiseAsset, GetActorLocation());
}
