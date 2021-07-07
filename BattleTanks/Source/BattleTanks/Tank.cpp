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
	AimComp = CreateDefaultSubobject<UTankAimingComponent>(TEXT("Aim Comp"));
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector AimLocation)
{
	AimComp->AimAt(AimLocation, LaunchSpeed);
}

void ATank::SetBarrelComponent(UTankBarrel* BarrelToSet)
{
	//Setting barrel mesh component to rotate when aiming
	AimComp->SetBarrelComponent(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretComponent(UTankTurret* TurretToSet)
{
	AimComp->SetTurretComponent(TurretToSet);
}

void ATank::Fire()
{
	if(!Barrel) return;

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileToSpawn, Barrel->GetSocketLocation(FName("Projectile")),
		Barrel->GetSocketRotation(FName("Projectile")));

	if(Projectile)
	{
		Projectile->LaunchProjectile(LaunchSpeed);
	}
	
}
