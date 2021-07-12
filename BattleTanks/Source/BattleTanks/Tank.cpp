// Fill out your copyright notice in the Description page of Project Settings.
#include "TankBarrel.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "Projectile.h"
#include "TankMovementComponent.h"

//TODO make a reloading system with firing delay
//Fix the AimComp pointer in Tank class
//Delete the BPImplementable event in TankPlayerController if it doesn't needed

//Sets default values
ATank::ATank()
{
 	//Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::AimAt(FVector AimLocation)
{
	if(!ensure(AimComp)) return;
	AimComp->AimAt(AimLocation, LaunchSpeed);
}


void ATank::Fire()
{

	if(!ensure(Barrel)) return;

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileToSpawn, Barrel->GetSocketLocation(FName("Projectile")),
		Barrel->GetSocketRotation(FName("Projectile")));

	if(ensure(Projectile))
	{
		Projectile->LaunchProjectile(LaunchSpeed);
	}
	
}
