// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

//Maybe bug is in the amount of force that we give to tank

void UTankTrack::SetThrottle(float Throttle)
{
	//Applying force
	//Calculating force to apply. Equals to 0, if throttle is 0
	FVector ForceToApply = this->GetForwardVector() * Throttle * TankMaxDrivingForce;
	//Getting track's location to apply a force on it
	FVector ForceLocation = GetComponentLocation();
	//Getting rootcomponent and casting to primitive component for applying force
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceToApply, ForceLocation);
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//Correcting slippage force
	//Finding out the slippage (skoljenye) speed of tracks
	float SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());

	//Calculating the required acceleration this frame to correct
	FVector CorrectionAcceleration = (-SlippageSpeed / DeltaTime) * GetRightVector();

	//Getting Tank Body static mesh to apply correction force
	UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	// Calculate and apply sideways (F = m * a) (Mass * Acceleration)
	FVector CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // Two tracks, that's why we are dividing it by two
	TankRoot->AddForce(CorrectionForce);
}
