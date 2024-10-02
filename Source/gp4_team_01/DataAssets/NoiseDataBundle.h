// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NoiseDataAsset.h"
#include "Engine/DataAsset.h"
#include "NoiseDataBundle.generated.h"

UCLASS()
class GP4_TEAM_01_API UNoiseDataBundle : public UPrimaryDataAsset {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	TArray<UNoiseDataAsset*>& GetEntries() { return Entries; };

	UFUNCTION(BlueprintCallable)
	UNoiseDataAsset* GetEntryByName(const FName Name) {
		if(Entries.IsEmpty())
			return nullptr;

		for (const auto& Entry : Entries) {
			if(Entry->Name == Name)
				return Entry;
		}
		return nullptr;
	}
 	
private:
	UPROPERTY(EditDefaultsOnly)
	TArray<UNoiseDataAsset*> Entries;
};
