// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankAimingComponent.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankBarrel;
class UTankTurret;
class AProjectile;


UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void AimAt(FVector AimLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetBarrelComponent(UTankBarrel* BarrelToSet);
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetTurretComponent(UTankTurret* TurretToSet);	

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();
	
private:
	
	UTankAimingComponent* AimComp;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float LaunchSpeed = 4000.f;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<AProjectile> ProjectileToSpawn;

	//Pointer to barrel for spawning a projectile
	UTankBarrel* Barrel;
	
};
