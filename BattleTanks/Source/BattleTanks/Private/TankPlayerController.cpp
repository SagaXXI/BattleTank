// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "BattleTanks/Tank.h"



void ATankPlayerController::BeginPlay()
{
   PrimaryActorTick.bCanEverTick = true;
   PrimaryActorTick.bStartWithTickEnabled = true;


   AimCompRef = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
   Super::Tick(DeltaTime);
   AimTowardsCrosshair();
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
   Super::SetPawn(InPawn);
   if(InPawn)
   {
      ATank* PlayerTank = Cast<ATank>(InPawn);
      if(!ensure(PlayerTank)) return;

      //Subscribe our local method to the tank's death event
      PlayerTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPlayerTankDeath);
   }
}

void ATankPlayerController::OnPlayerTankDeath()
{
   StartSpectatingOnly();
}

void ATankPlayerController::AimTowardsCrosshair()
{
   if (!AimCompRef) return;
   
   //This is OUTPARAMETER 
   FVector HitLocation;

   //If ray which we are tracing hits something, then we are going to turn the turret and elevate the tank barrel
   //bool bGotHitLocation = GetSightRayHitLocation(OUT HitLocation);
   //UE_LOG(LogTemp, Warning, TEXT("%i"), bGotHitLocation)
   //if(bGotHitLocation)
   if(GetSightRayHitLocation(OUT HitLocation))
   {
      AimCompRef->AimAt(HitLocation);
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
      return GetLookVectorHitLocation(LookDirection, OUT HitLocation);
    
   }
   return false;
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
         ECollisionChannel::ECC_Camera)
         )
   {
      HitLocation = HitResult.Location;
      return true;
   }
   return false;
}

