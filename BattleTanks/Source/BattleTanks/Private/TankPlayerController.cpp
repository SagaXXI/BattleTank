// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks/Tank.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
   PrimaryActorTick.bCanEverTick = true;
   PrimaryActorTick.bStartWithTickEnabled = true;
   
   auto ControlledTank = GetControlledTank();
   if(!ControlledTank)
   {
      UE_LOG(LogTemp, Error, TEXT("This PlayerController currently is not possesing any pawn!"));
   }
   else
   {
      UE_LOG(LogTemp, Warning, TEXT("This PlayerController is possesing: %s"), *ControlledTank->GetName());
   }
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
   if(!GetControlledTank()) return;

   //This is OUTPARAMETER 
   FVector HitLocation;
   if(GetSightRayHitLocation(HitLocation))
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
   //UE_LOG(LogTemp, Warning, TEXT("The crosshair location on screen is: %s"), *ScreenLocation.ToString())
   //
   //Getting the direction, where our screen is directing in world
   FVector LookDirection;
   if(GetLookDirection(ScreenLocation, LookDirection))
   {
      if(GetLookVectorHitLocation(LookDirection, HitLocation))
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

