// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) return;
	RightTrack->SetThrottle(Throw);
	LeftTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) return;
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	//AI tank's forward vector
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	//AI tank's movememnt intention (where it should move)
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();

	//Getting the dot product of two vectors, for example if player tank is on the right-forward side (diagonal) of ai tank, it will find
	//the dot product of both given vectors and final value will be 1, then it will need to go forward to be on the same line where player tank is.
	float ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(ForwardThrow);

	//Getting the cross product of two vectors, so if player tank is staying on the right side of ai tank, it will find the cross product between
	//both given vectors, and find the Z vector of it, because cross product returns fvector
	float RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendTurnRight(RightThrow);
	
	
	UE_LOG(LogTemp, Warning, TEXT("Forward %f, Right %f"), ForwardThrow, RightThrow);
	
} 
