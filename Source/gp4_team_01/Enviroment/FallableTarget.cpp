// Fill out your copyright notice in the Description page of Project Settings.


#include "FallableTarget.h"

#include "gp4_team_01/Enemies/EnemyBase.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AFallableTarget::AFallableTarget() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	FallingTarget = CreateDefaultSubobject<USceneComponent>("Falling Target");
	FallingTarget->SetupAttachment(RootComponent);

	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFallableTarget::BeginPlay() {
	Super::BeginPlay();

	FallingTargetVector = FallingTarget->GetComponentLocation();
}

void AFallableTarget::OnInteract() {
	bIsFalling = true;
}

// Called every frame
void AFallableTarget::Tick(float DeltaTime) {
	if(!bIsFalling)
		return;

	SetActorLocation(UKismetMathLibrary::VInterpTo_Constant(GetActorLocation(), FallingTargetVector, DeltaTime, FallingSpeed));

	if(GetActorLocation() == FallingTargetVector)
		OnBreak();
		
}

void AFallableTarget::OnBreak() {
	UE_LOG(LogTemp, Warning, TEXT("Fallable broke!"));

	bIsFalling = false;

	if(bKillsEnemyOnFall)
		EnemyToKill->OnDeath(this);

	//TODO: handle graphics for the break
	Destroy();
}
