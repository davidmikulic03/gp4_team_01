// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ThrowableInventory.generated.h"

class APlayerCharacter;

UENUM(BlueprintType)
enum class ItemType : uint8 {
	None = 0,
	Throwable,
	SmokeBomb
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GP4_TEAM_01_API UThrowableInventory : public UActorComponent
{
	GENERATED_BODY()
//methods 
public:	
	UThrowableInventory();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//getters and setters

	void AddPlayerRef(APlayerCharacter* Player) { PlayerRef = Player; };
	
	UFUNCTION(BlueprintCallable)
	int GetCurrentCount(ItemType Type) const;
	UFUNCTION(BlueprintCallable)
	bool CanFitMoreItemOfType(ItemType Type) const;
	UFUNCTION(BlueprintCallable)
	void RemoveItem(ItemType Type);
	UFUNCTION(BlueprintCallable)
	void AddItem(ItemType Type);
	UFUNCTION(BlueprintCallable)
	void AddAmountToInventory(ItemType Type, int AmountToAdd);
	
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Inventory")
	int MaxThrowables = 12;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Inventory")
	int CurrentThrowables = 3;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Inventory")
	int MaxSmokeBombs = 5;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Inventory")
	int CurrentSmokeBombs = 0;

private:
	APlayerCharacter* PlayerRef;

	int SavedThrowables = 0;
	int SavedSmokeBombs = 0;
};
