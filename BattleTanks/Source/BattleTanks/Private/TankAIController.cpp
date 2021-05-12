// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "BattleTanks/Tank.h"

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay()
{
	auto ControlledTank = GetControlledTank();
	if(!ControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("This AIController currently is not possesing any pawn!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("This AIController is possesing: %s"), *ControlledTank->GetName());
	}
}
