// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

//TODO fix the issue with the -180 and 180 degrees
//You need to convert it to 360 degrees system

void UTankTurret::Rotate(float RelativeSpeed)
{
	float Time = GetWorld()->GetTimeSeconds();
	
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	
	//This is where we calculate our elevation from the position before.
	//(DeltaTimeSeconds is for delay between frames, to avoid the slower or faster function running on different machines)
	float RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	
	//Raw elevation, which is not clamped yet
	float Rotation = GetRelativeRotation().Yaw + RotationChange;
	
	//Sets the rotation of the component relative to its parent
	SetWorldRotation(FRotator(0, Rotation, 0));
}


