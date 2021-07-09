// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	// ...
}
        
void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if(!Barrel) return;
	if(!Turret) return;
	
	//Velocity, that will be set
	FVector OutLaunchVelocity;
	FVector StartPoint = Barrel->GetSocketLocation(TEXT("Projectile"));
	
	//Calculates an launch velocity for a projectile to hit a specified point.
	//This is done for precise shooting
	bool bHasAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		GetWorld(),
		OutLaunchVelocity,
		StartPoint,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
		);
	
	if(bHasAimSolution)
	{
		//Turns this OutLaunchVelocity vector to a normal vector (a unit vector, that equals to 1 with direction)
		FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
	else
	{
		
	}
	
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if(!Barrel || !Turret) return;
	//Getting delta rotator between barrel forward vector and aim direction, turret forward vector and aim direction,
	//because to rotate them, we need delta vector, like in FindLookAtLocation()
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	//These will get the right rotator for elevate and rotate function. AimDirection, which we are looking now in game minus barrel's or turret's current rotation
	FRotator DeltaRotation = AimAsRotator - BarrelRotation;
	
	
	//Elevating barrel up	
	//If pitch has minus value, speed will be -1
	//If pitch has plus value, speed will be +1
	//This will help us avoid the -180 and 180 degrees clamp on tank turret
	if (FMath::Abs(DeltaRotation.Yaw) < 180)
	{
		Turret->Rotate(DeltaRotation.Yaw);
	}
	else // Avoid going the long-way round
	{
	Turret->Rotate(-DeltaRotation.Yaw);
	}
	//Rotating turret	
	//If yaw has minus value, speed will be -1
	//If yaw has plus value, speed will be +1
	Barrel->Elevate(DeltaRotation.Pitch);
}
