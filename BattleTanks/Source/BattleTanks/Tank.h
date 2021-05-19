// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankAimingComponent.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankBarrel;

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void AimAt(FVector AimLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetBarrelComponent(UTankBarrel* BarrelToSet);
	
protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

private:
	UTankAimingComponent* AimComp;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	float LaunchSpeed = 4000.f;
	
};
