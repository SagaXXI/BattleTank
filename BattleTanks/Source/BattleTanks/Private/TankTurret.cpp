// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	auto Time = GetWorld()->GetTimeSeconds();
	
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	
	//This is where we calculate our elevation from the position before.
	//(DeltaTimeSeconds is for delay between frames, to avoid the slower or faster function running on different machines)
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	
	//Raw elevation, which is not clamped yet
	auto RawNewRotation = GetRelativeRotation().Pitch + RotationChange;
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *GetRelativeRotation().ToString())
	
	//Clamped current relative rotation + elevation change 
	auto Rotation = FMath::Clamp<float>(RawNewRotation, MinRotationDegrees, MaxRotationDegrees);
	/*APawn* PlayerPawn = Cast<APawn>(GetOwner());
	if(PlayerPawn->IsPlayerControlled())
	{
	UE_LOG(LogTemp, Warning, TEXT("%f"), Elevation)
	UE_LOG(LogTemp, Warning, TEXT("At %f barrel elevated with %f speed"), Time, RelativeSpeed)
	}*/
	
	
	//Sets the rotation of the component relative to its parent
	SetRelativeRotation(FRotator(0, Rotation, 0));
}
