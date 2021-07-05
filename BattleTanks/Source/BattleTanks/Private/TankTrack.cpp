// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

//Maybe bug is in the amount of force that we give to tank

void UTankTrack::SetThrottle(float Throttle)
{
	//Apllying force
	//Calculating force to apply. Equals to 0, if throttle is 0
	FVector ForceToApply = this->GetForwardVector() * Throttle * TankMaxDrivingForce;
	//Getting track's location to apply a force on it
	FVector ForceLocation = GetComponentLocation();
	//Getting rootcomponent and casting to primitive component for applying force
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceToApply, ForceLocation);
}
