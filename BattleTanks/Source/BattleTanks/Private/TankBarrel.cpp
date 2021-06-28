// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	float Time = GetWorld()->GetTimeSeconds();
	
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	
	//This is where we calculate our elevation from the position before.
	//(DeltaTimeSeconds is for delay between frames, to avoid the slower or faster function running on different machines)
	float ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	
	//Raw elevation, which is not clamped yet
	float RawNewElevation = GetRelativeRotation().Pitch + ElevationChange;
	
	//Clamped current relative rotation + elevation change 
	float Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	
	//Sets the rotation of the component relative to its parent
	SetRelativeRotation(FRotator(Elevation, 0, 0));
}

