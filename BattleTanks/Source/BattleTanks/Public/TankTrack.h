// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class BATTLETANKS_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	//Max force to apply for tracks to move (in Newtons (mass * acceleration))
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float TankMaxDrivingForce = 400000.f;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	void DriveTrack();

	float CurrentThrottle = 0;

public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);

	//Force to correct the slippage (friction)
	void ApplyCorrectionForce();

	UTankTrack();


	
};
