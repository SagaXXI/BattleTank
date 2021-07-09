// Fill out your copyright notice in the Description page of Project Settings.
#include "TankBarrel.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "Projectile.h"
#include "TankMovementComponent.h"


//Sets default values
ATank::ATank()
{
 	//Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::AimAt(FVector AimLocation)
{
	AimComp->AimAt(AimLocation, LaunchSpeed);
}


void ATank::Fire()
{
	//TODO make a reloading system with firing delay
	if(!Barrel) return;

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileToSpawn, Barrel->GetSocketLocation(FName("Projectile")),
		Barrel->GetSocketRotation(FName("Projectile")));

	if(Projectile)
	{
		Projectile->LaunchProjectile(LaunchSpeed);
	}
	
}
