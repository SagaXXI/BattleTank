// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

//Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY()
	UTankTurret* Turret;
	
	UPROPERTY()
	UTankBarrel* Barrel;

	void MoveBarrelTowards(FVector AimDirection);
	
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<AProjectile> ProjectileToSpawn;

	//Launching speed for projectile and to calculate trajectory
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float LaunchSpeed = 4000.f;
	
public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	//Used to move barrel and turret (for aiming)
	void AimAt(FVector HitLocation);

	//Initialising all pointers and variables that we need in BP
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	//Function for firing on tank
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

protected:
	
	//Enum variable for aiming state. (To change color of crosshair at different situations
	UPROPERTY(BlueprintReadOnly, Category = "Crosshair")
	EFiringState FiringState = EFiringState::Locked;
};
