// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;
UCLASS(meta=(BlueprintSpawnableComponent))
class BATTLETANKS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
public:

	//Function for setting tracks
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	//Giving throttle and moving the tracks to move forward or backwards
	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveForward(float Throw);

	//Giving throttle to tracks to turn right or left
	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendTurnRight(float Throw);

protected:
	// Called from the pathfinding logic by the AI controllers
	void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
	
	
};
