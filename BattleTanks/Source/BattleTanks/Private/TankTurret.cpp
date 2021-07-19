// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"


void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	
	//This is where we calculate our elevation from the position before.
	//(DeltaTimeSeconds is for delay between frames, to avoid the slower or faster function running on different machines)
	float RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->GetDeltaSeconds();
	
	//Raw elevation, which is not clamped yet
	float Rotation = GetRelativeRotation().Yaw + RotationChange;
	
	//Sets the rotation of the component relative to its parent
	SetRelativeRotation(FRotator(0, Rotation, 0));
}


