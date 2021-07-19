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
	Locked,
	NoAmmo
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

	void MoveBarrelTowards(FVector AimingDirection);
	
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<AProjectile> ProjectileToSpawn;

	//Launching speed for projectile and to calculate trajectory
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float LaunchSpeed = 4000.f;

	//Reloading mechanics
	//Reloading delay for tank
	UPROPERTY(EditAnywhere)
	float ReloadDelay = 3.f;

	int32 Ammo;

	//When tank fired last time
	float LastTimeFired = 0.f;

	FVector AimDirection;

	//Method for changing crosshair color mechanics
	bool IsBarrelMoving();
	
	
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

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	virtual void BeginPlay() override;

	EFiringState GetFiringState() const;

	//Reloading mechanics
	UPROPERTY(EditAnywhere, Category = "Reload")
	int32 MaxAmmo = 3;

	//Gets current ammo for UI
	UFUNCTION(BlueprintCallable, Category = "Ammo")
	int32 GetCurrentAmmo() const;

protected:
	
	//Enum variable for aiming state. (To change color of crosshair at different situations
	UPROPERTY(BlueprintReadOnly, Category = "Crosshair")
	EFiringState FiringState = EFiringState::Reloading;
};
