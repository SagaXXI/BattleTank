// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Adding projectile movement component
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}


void AProjectile::LaunchProjectile(float Speed)
{
	//Sets the velocity to the new value, rotated into Actor space.
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	//Not sure what it is, check it out, ok?
	ProjectileMovement->Activate();
}

