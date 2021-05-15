// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
   GENERATED_BODY()

public:
   
   void BeginPlay() override;
   
   void Tick(float DeltaTime) override;
   
private:

   ATank* GetControlledTank() const;
   
   //Returns true if we hit a landscape
   bool GetSightRayHitLocation(FVector &OutHitLocation) const;

   //Move the barrel to crosshair, like in World of Tanks
   void AimTowardsCrosshair();
   
   UPROPERTY(EditAnywhere)
   float CrosshairXLocation = 0.5f;
   
   UPROPERTY(EditAnywhere)
   float CrosshairYLocation = 0.3333f;
};
