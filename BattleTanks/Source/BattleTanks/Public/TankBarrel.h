// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class BATTLETANKS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	//If barrel is moving down, the value will be -1, if it is moving up, the value will be +1
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere, Category = "Setup")
	float MaxDegreesPerSecond = 5.f;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float MaxElevationDegrees = 40.f;
	
	UPROPERTY(EditAnywhere, Category = "Setup")
	float MinElevationDegrees = 0.f;
};
