#pragma once

class UNoiseDataAsset;

class GP4_TEAM_01_API INoiseMaker {
public:
	virtual ~INoiseMaker() = default;

protected:
	virtual void GenerateNoise(UNoiseDataAsset* NoiseDataAsset, FVector Location) = 0;
};
