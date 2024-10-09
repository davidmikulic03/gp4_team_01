#include "Magnet.h"

AMagnet::AMagnet() {
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	TraversalTarget = CreateDefaultSubobject<USceneComponent>("Traversal Target");
	AimTarget = CreateDefaultSubobject<USceneComponent>("Aim Target");
	TraversalTarget->SetupAttachment(RootComponent);
	AimTarget->SetupAttachment(RootComponent);
	
	PrimaryActorTick.bCanEverTick = false;
}

void AMagnet::BeginPlay() {
	Super::BeginPlay();
	
}
