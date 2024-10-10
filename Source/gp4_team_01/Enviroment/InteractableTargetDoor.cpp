#include "InteractableTargetDoor.h"

#include "Kismet/KismetMathLibrary.h"


AInteractableTargetDoor::AInteractableTargetDoor() {
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	Target = CreateDefaultSubobject<USceneComponent>("Target");
	Target->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AInteractableTargetDoor::BeginPlay() {
	Super::BeginPlay();

	StartingPosition = GetActorLocation();
	TargetVector = Target->GetComponentLocation();
}

// Called every frame
void AInteractableTargetDoor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if(!bIsMoving)
		return;

	SetActorLocation(UKismetMathLibrary::VInterpTo_Constant(GetActorLocation(), TargetVector, DeltaTime, Speed));

	if(GetActorLocation() == TargetVector)
		bIsMoving = false;
}

void AInteractableTargetDoor::OnInteract() {
	bIsMoving = true;
}

void AInteractableTargetDoor::OnUnInteract() {
	SetActorLocation(StartingPosition);
}

