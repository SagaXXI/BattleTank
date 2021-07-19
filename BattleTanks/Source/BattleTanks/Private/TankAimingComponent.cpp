// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;

}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastTimeFired = GetWorld()->GetTimeSeconds();

	Ammo = MaxAmmo;
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (Ammo <= 0)
	{
		FiringState = EFiringState::NoAmmo;
	}
	else if((GetWorld()->GetTimeSeconds() - LastTimeFired) < ReloadDelay)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	
	else
	{
		FiringState = EFiringState::Locked;
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	FVector BarrelForward = Barrel->GetForwardVector();
	//Check against another vector for equality, within specified error limits.
	//FVectors are structs that contain floats in it, so when we are comparing floats, we can't just say that they are equal, it depends on value after floating point.
	//This is why we specified a tolerance (limit) to compare them.
	//Here is not logic action (!), because if two vectors (forward vector and aim direction) are equal, then barrel is staying at one place and doesn't moving
	return !BarrelForward.Equals(AimDirection, 0.01); 
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if(!ensure(Barrel)) return;
	if(!ensure(Turret))return;
	
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
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
	
}

void UTankAimingComponent::Fire()
{
	if(FiringState == EFiringState::Aiming || FiringState == EFiringState::Locked)
	{
		if(!ensure(Barrel)) return;
		if(!ensure(ProjectileToSpawn)) return;
		
		//Spawning projectile
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileToSpawn, Barrel->GetSocketLocation(FName("Projectile")),
		Barrel->GetSocketRotation(FName("Projectile")));

		//Giving a launchspeed to projectile
		Projectile->LaunchProjectile(LaunchSpeed);
		Ammo--;
		//Saving last fired time for reloading
		LastTimeFired = GetWorld()->GetTimeSeconds();
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimingDirection)
{
	if (!ensure(Barrel && Turret)) return;
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

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

int32 UTankAimingComponent::GetCurrentAmmo() const
{
	return Ammo;
}