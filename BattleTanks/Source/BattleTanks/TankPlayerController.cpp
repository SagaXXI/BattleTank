// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
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

