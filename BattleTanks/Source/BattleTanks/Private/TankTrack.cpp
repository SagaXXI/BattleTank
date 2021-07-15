// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

//Maybe bug is in the amount of force that we give to tank

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}


void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	//We are doing this in other function and setting the throttle when pressing input keys, because we need to prevent applying force when tank is on the air
	DriveTrack();
	ApplyCorrectionForce();
	//Setting to zero to stop applying force
	CurrentThrottle = 0;
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{
	//Applying force
	//Calculating force to apply. Equals to 0, if throttle is 0
	FVector ForceToApply = this->GetForwardVector() * CurrentThrottle * TankMaxDrivingForce;
	//Getting track's location to apply a force on it
	FVector ForceLocation = GetComponentLocation();
	//Getting rootcomponent and casting to primitive component for applying force
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceToApply, ForceLocation);
}



void UTankTrack::ApplyCorrectionForce()
{
	//Correcting slippage force
	//Finding out the slippage (skoljenye) speed of tracks
	float SlippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());

	//This time is needed to calculate the acceleration for correction force
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	//Calculating the required acceleration this frame to correct
	FVector CorrectionAcceleration = (-SlippageSpeed / DeltaTime) * GetRightVector();

	//Getting Tank Body static mesh to apply correction force
	UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	// Calculate and apply sideways (F = m * a) (Mass * Acceleration)
	FVector CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // Two tracks, that's why we are dividing it by two
	TankRoot->AddForce(CorrectionForce);
}

