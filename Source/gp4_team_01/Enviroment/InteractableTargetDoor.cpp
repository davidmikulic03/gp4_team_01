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
	CurrentFadeTimer = .0f;
}

// Called every frame
void AInteractableTargetDoor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if(!bIsOpening && !bIsClosing)
		return;

	if(bFadesOutOnInteraction)
		FadeOpen(DeltaTime);
	else
		Move(DeltaTime);
}

void AInteractableTargetDoor::OnInteract() {
	if(!bIsOpening && !bIsClosing) {
		bIsOpening = true;
		bHasBeenInteractedWith = true;
	}
}

void AInteractableTargetDoor::OnUnInteract() {
	if(!bIsOpening && !bIsClosing) {
		bIsClosing = true;
		bHasBeenInteractedWith = false;
	}
}

void AInteractableTargetDoor::Move(float DeltaTime)
{
	SetActorLocation(UKismetMathLibrary::VInterpTo_Constant(GetActorLocation(), bIsOpening ? TargetVector : StartingPosition, DeltaTime, Speed));
 
	if(bIsOpening) {
		if(GetActorLocation() == TargetVector)
			bIsOpening = false;
	} else if (bIsClosing) {
		if(GetActorLocation() == StartingPosition)
			bIsClosing = false;
	}
}

void AInteractableTargetDoor::FadeOpen(float DeltaTime)
{
	CurrentFadeTimer += DeltaTime;

	if(CurrentFadeTimer >= TimeToFadeOpen) {
		
		CurrentFadeTimer = 0;
		if(bIsOpening) {
			SetActorEnableCollision(false);
			bIsOpening = false;
		} else if (bIsClosing) {
			SetActorEnableCollision(true);
			bIsClosing = false;
		}
	}
}

