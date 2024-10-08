// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ThrowableInventory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GP4_TEAM_01_API UThrowableInventory : public UActorComponent
{
	GENERATED_BODY()
//methods 
public:	
	UThrowableInventory();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//getters and setters
	UFUNCTION()
	int GetCurrentCount();
	UFUNCTION()
	void DecrementNumberOfThrowables();
	UFUNCTION()
	void IncrementNumberOfThrowables();
	UFUNCTION()
	void AddAmountToInventory(int AmountToAdd);
protected:
	virtual void BeginPlay() override;
private:	

//variables
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Throwables")
	int MaxNumberOfThrowables = 12;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Throwables")
	int CurrentNumberOfThrowables = 3;
protected:
private:


		
};
