// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks/Tank.h"
#include "TankPlayerController.h"
#include "TankAimingComponent.h"


void ATankPlayerController::BeginPlay()
{
   PrimaryActorTick.bCanEverTick = true;
   PrimaryActorTick.bStartWithTickEnabled = true;
   
   /*auto AimComp = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
   if(AimComp)
   {
      FindAndSetAimComp(AimComp);
   }
   else
   {
      UE_LOG(LogTemp, Warning, TEXT("Player controller can't find aiming component at Begin Play"))
   }*/
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
   Super::Tick(DeltaTime);
   AimTowardsCrosshair();

}

ATank* ATankPlayerController::GetControlledTank() const
{
   return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
   if (!ensure(GetControlledTank())) return;
   
   //This is OUTPARAMETER 
   FVector HitLocation;

   //If ray which we are tracing hits something, then we are going to turn the turret and elevate the tank barrel
   if(GetSightRayHitLocation(OUT HitLocation))
   {
      GetControlledTank()->AimAt(HitLocation);
      //UE_LOG(LogTemp, Warning, TEXT("The hit location is: %s"), *HitLocation.ToString())
   }
}

bool ATankPlayerController::GetSightRayHitLocation(FVector OUT &HitLocation) const
{
   //Finding crosshair location in pixel coordinates
   //Getting viewport size
   int32 ViewportXSize, ViewportYSize;
   GetViewportSize(ViewportXSize, ViewportYSize);
   
   //Getting crosshair location on screen, with size
   FVector2D ScreenLocation = FVector2D(ViewportXSize * CrosshairXLocation, ViewportYSize * CrosshairYLocation);
   
   //Getting the direction, where our screen is directing in world
   FVector LookDirection;
   
   //Projecting crosshair location to screen and getting the look direction, for linetrace
   if(GetLookDirection(ScreenLocation, OUT LookDirection))
   {
      //Doing line trace and getting hit location
      if(GetLookVectorHitLocation(LookDirection, OUT HitLocation))
      {
         //UE_LOG(LogTemp, Warning, TEXT("Your crosshair is pointing to %s in world"), *HitLocation.ToString());
      }
   }
   return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{  
   FVector CameraWorldLocation;
   return DeprojectScreenPositionToWorld
   (ScreenLocation.X,
      ScreenLocation.Y,
      CameraWorldLocation,
      LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const
{
   FVector StartLocation = PlayerCameraManager->GetCameraLocation();
   FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);
   FHitResult HitResult;
   if(GetWorld()->LineTraceSingleByChannel(
      HitResult,
         StartLocation,
         EndLocation,
         ECollisionChannel::ECC_Visibility)
         )
   {
      HitLocation = HitResult.Location;
      return true;
   }
   return false;
}

