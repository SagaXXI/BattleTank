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

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY()
	UTankTurret* Turret;
	
	UPROPERTY()
	UTankBarrel* Barrel;

	void MoveBarrelTowards(FVector AimDirection);
	
public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector HitLocation, float LaunchSpeed);
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

protected:
	
	//Enum variable for aiming state. (To change color of crosshair at different situations
	UPROPERTY(BlueprintReadOnly, Category = "Crosshair")
	EFiringState FiringState = EFiringState::Locked;
};
