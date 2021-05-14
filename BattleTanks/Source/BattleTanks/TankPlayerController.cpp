// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
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
		//UE_LOG(LogTemp, Warning, TEXT("The hit location is: %s"), *HitLocation.ToString())
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector OUT &HitLocation) const
{
	int32 ViewportXSize, ViewportYSize;
	GetViewportSize(ViewportXSize, ViewportYSize);
	FVector2D ScreenLocation = FVector2D(ViewportXSize * CrosshairXLocation, ViewportYSize * CrosshairYLocation);
	UE_LOG(LogTemp, Warning, TEXT("The crosshair location on screen is: %s"), *ScreenLocation.ToString())
	return true;
}

