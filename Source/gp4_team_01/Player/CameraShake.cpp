// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraShake.h"

UCameraShake::UCameraShake()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UCameraShake::BeginPlay()
{
	Super::BeginPlay();
	if(Camera == nullptr)
	{

		Camera = GetPlayerCamera();
		OriginalCameraPosition = Camera->GetRelativeLocation();
		OriginalCameraRotation = Camera->GetRelativeRotation();
		DebugMessage();
	}
}

void UCameraShake::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(Camera != nullptr)
		//safety check - TODO: See if Camera stuff can be set from here, or if I need to do a setter function in the PlayerCharacter
		//TODO: After lunch - test through UE_LOG how the values change and use dummy variables to see if your manual lerps work
		//when I say manual I mean the included math library
	{
		//possible nesting overdrive
		//this should return camera only if camera is not at original position
		if(Camera->GetRelativeRotation() != OriginalCameraRotation &&
			Camera->GetRelativeLocation() != OriginalCameraPosition &&
			!bCameraShakeOn)
		{
			FRotator NewRotation = FMath::Lerp(Camera->GetRelativeRotation(), OriginalCameraRotation, 1.f * DeltaTime);
			FVector NewPosition = FMath::Lerp(Camera->GetRelativeLocation(), OriginalCameraPosition, 1.f * DeltaTime);
			Camera->SetRelativeRotation(NewRotation);
			Camera->SetRelativeLocation(NewPosition);
			UE_LOG(LogTemp, Warning, TEXT("New Position: %f, %f, %f"), NewPosition.X, NewPosition.Y, NewPosition.Z);
			UE_LOG(LogTemp, Warning, TEXT("New Rotation: %f, %f, %f"), NewRotation.Vector().X, NewRotation.Vector().Y, NewRotation.Vector().Z);
		}
		else if(bCameraShakeOn)
		{
			CameraShake(1.f); //TODO remove the magic number. See if it makes any sense for the function to take in anything.
		}
		
	}
}

UCameraComponent* UCameraShake::GetPlayerCamera()
{
	UWorld* CurrentWorld = GetWorld();
	if(CurrentWorld != nullptr)
	{
		APlayerController* CurrentController = CurrentWorld->GetFirstPlayerController();
		if(CurrentController != nullptr)
		{
			APawn* CurrentPlayer = CurrentController->GetPawn();
			if(CurrentPlayer != nullptr)
			{
				return CurrentPlayer->FindComponentByClass<UCameraComponent>();
			}
		}
	}
	return nullptr;
}

void UCameraShake::CameraShake(float InputValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Camera Shaking, wob wob wob"));
}

//temp debugging functions
void UCameraShake::DebugMessage()
{
	UE_LOG(LogTemp, Warning, TEXT("Camera Assigned"));
	UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f"), OriginalCameraPosition.X, OriginalCameraPosition.Y, OriginalCameraPosition.Z);
	UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f"), OriginalCameraRotation.Vector().X, OriginalCameraRotation.Vector().Y, OriginalCameraRotation.Vector().Z);
}