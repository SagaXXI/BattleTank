// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}



void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	//Applying force
	//Calculating force to apply. Equals to 0, if throttle is 0
	float ForceToApply = CurrentThrottle * TankMaxDrivingForce;
	//Getting wheels to apply a force on them
	TArray<ASprungWheel*> Wheels = GetWheels();
	//Calculating every wheel's force to apply
	float ForcePerWheel = ForceToApply / Wheels.Num();
	//Applying force on every wheel
	for(auto Wheel : Wheels)
	{
		if(!ensure(Wheel)) return;
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray <ASprungWheel*> SprungWheels;
	//Used to get all child comps of track
	TArray <USceneComponent*> ChildComps;
	//Getting all children comps of track
	GetChildrenComponents(true, ChildComps);
	//Iterating through them
	for (USceneComponent* Child : ChildComps)
	{
		if(!ensure(Child)) continue;
		//Checking if it is a SpawnPoint comp
		USpawnPoint* SpawnPoint = Cast<USpawnPoint>(Child);
		if(!SpawnPoint) continue;

		//Checking if there is SprungWheel actor spawned
		ASprungWheel* SprungWheel = Cast<ASprungWheel>(SpawnPoint->GetSpawnedActor());
		if(!SprungWheel) continue;

		//Adding it to Wheels array
		SprungWheels.Add(SprungWheel);
	}
	return SprungWheels;
}


