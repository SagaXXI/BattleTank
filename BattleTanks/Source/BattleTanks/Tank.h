// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankAimingComponent.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class AProjectile;


UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	/*UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();
	*/
	
private:
	
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<AProjectile> ProjectileToSpawn;

	//Pointer to barrel for spawning a projectile
	UPROPERTY()
	UTankBarrel* Barrel;

protected:

	virtual void BeginPlay() override;

};
