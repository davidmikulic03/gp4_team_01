// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrowableInventory.h"

// Sets default values for this component's properties
UThrowableInventory::UThrowableInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UThrowableInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UThrowableInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int UThrowableInventory::GetCurrentCount()
{
	return CurrentNumberOfThrowables;
}

void UThrowableInventory::DecrementNumberOfThrowables()
{
	CurrentNumberOfThrowables--;
	if(CurrentNumberOfThrowables <= 0)
	{
		CurrentNumberOfThrowables = 0;
	}
}

void UThrowableInventory::IncrementNumberOfThrowables()
{
	CurrentNumberOfThrowables++;
	if(CurrentNumberOfThrowables >= MaxNumberOfThrowables)
	{
		CurrentNumberOfThrowables = MaxNumberOfThrowables;		
	}
}

void UThrowableInventory::AddAmountToInventory(int AmountToAdd)
{
	CurrentNumberOfThrowables+= AmountToAdd;
	if(CurrentNumberOfThrowables >= MaxNumberOfThrowables)
	{
		CurrentNumberOfThrowables = MaxNumberOfThrowables;
	}
	else if(CurrentNumberOfThrowables== MaxNumberOfThrowables)
	{
		return;
	}
}

