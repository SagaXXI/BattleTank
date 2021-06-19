// Fill out your copyright notice in the Description page of Project Settings.
#include "TankBarrel.h"
#include "Tank.h"
#include "TankAimingComponent.h"

//TODO check aim towards crosshair in player controller

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
}
