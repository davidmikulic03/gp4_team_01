//#include "NoiseMaker.h"
//
//#include "Components/SphereComponent.h"
//#include "Components/StaticMeshComponent.h"
//
//
//ANoiseMaker::ANoiseMaker() {
//	Root = CreateDefaultSubobject<USceneComponent>("Root");
//	SetRootComponent(Root);
//
//	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
//	Mesh->SetupAttachment(Root);
//
//	Mesh->OnComponentHit.AddDynamic(this, &ANoiseMaker::OnHit);
//	
//	PrimaryActorTick.bCanEverTick = true;
//}
//
//void ANoiseMaker::BeginPlay() {
//	Super::BeginPlay();
//}
//
//void ANoiseMaker::Tick(float DeltaTime) {
//	Super::Tick(DeltaTime);
//}
//
//void ANoiseMaker::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
//	FVector NormalImpulse, const FHitResult& Hit) {
//
//	if(bMakesNoiseOnCollision)
//		GenerateNoise(OtherActor);
//}
//
//void ANoiseMaker::GenerateNoise(AActor* Other) {
//	GEngine->AddOnScreenDebugMessage(123, 2.f, FColor::Yellow ,
//		FString::Printf(TEXT("Making noise after colliding with %s"), *Other->GetName()));
//}
