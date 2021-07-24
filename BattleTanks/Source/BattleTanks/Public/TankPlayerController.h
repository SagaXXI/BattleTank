// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
class UTankAimingComponent;

UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
   GENERATED_BODY()

	//Reference to aiming component for aiming towards crosshair
	UTankAimingComponent* AimCompRef;
	
	//Returns true if we hit a landscape
	bool GetSightRayHitLocation(FVector &OutHitLocation) const;

	//Move the barrel to crosshair, like in World of Tanks. And it happens every frame.
	void AimTowardsCrosshair();
   
	//Getting the direction, where we are looking. So, basically, this will project the direction vector through our screen to world
	//Projecting camera view to world
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	//Getting the location, where the trace, which is traced through our crosshair hits the world
	bool GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const;
   
	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5f;
   
	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.3333f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.f;\


public:
   
   void BeginPlay() override;
   
   void Tick(float DeltaTime) override;

   virtual void SetPawn(APawn* InPawn) override;

   UFUNCTION()
   void OnPlayerTankDeath();

};
