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

void UCameraShake::ToggleCameraShake()
{
	bCameraShakeOn = !bCameraShakeOn;

	if(bCameraShakeOn)
	{
		//camera shake functionality
	}
	else if(!bCameraShakeOn && Camera->GetRelativeLocation() == OriginalCameraPosition)
	{
		//return everything to normal
	}
}

//temp debugging functions
void UCameraShake::DebugMessage()
{
	UE_LOG(LogTemp, Warning, TEXT("Camera Assigned"));
}