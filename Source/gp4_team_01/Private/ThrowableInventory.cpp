// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrowableInventory.h"

UThrowableInventory::UThrowableInventory()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UThrowableInventory::BeginPlay()
{
	Super::BeginPlay();
}


void UThrowableInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

int UThrowableInventory::GetCurrentCount(const ItemType Type) const {
	if(Type == ItemType::Throwable)
		return CurrentThrowables;
	else if(Type == ItemType::SmokeBomb)
		return  CurrentSmokeBombs;
	
	return -1;
}

bool UThrowableInventory::CanFitMoreItemOfType(const ItemType Type) const {
	if(Type == ItemType::Throwable)
		return CurrentThrowables < MaxThrowables;
	else if (Type == ItemType::SmokeBomb)
		return CurrentSmokeBombs < MaxSmokeBombs;
	
	return false;
}

void UThrowableInventory::RemoveItem(const ItemType Type)
{
	AddAmountToInventory(Type, -1);
}

void UThrowableInventory::AddItem(const ItemType Type)
{
	AddAmountToInventory(Type, 1);
}

void UThrowableInventory::AddAmountToInventory(const ItemType Type, const int AmountToAdd)
{
	if(Type == ItemType::Throwable)
		CurrentThrowables = FMath::Clamp(CurrentThrowables + AmountToAdd, 0, MaxThrowables);
	else if(Type == ItemType::SmokeBomb)
		CurrentSmokeBombs = FMath::Clamp(CurrentSmokeBombs + AmountToAdd, 0, MaxSmokeBombs);
}

