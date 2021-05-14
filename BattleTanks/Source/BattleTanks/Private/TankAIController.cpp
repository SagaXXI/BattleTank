// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "BattleTanks/Tank.h"
#include "Kismet/GameplayStatics.h"


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

	auto PlayerTank = GetPlayerTank();
	if(!PlayerTank)
	{
		UE_LOG(LogTemp, Error, TEXT("This AIController didn't find the PlayerTank!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("This AIController found a player tank, which is %s"), *PlayerTank->GetName());
	}
	
}



ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if(!PlayerPawn) return nullptr;
	return Cast<ATank>(PlayerPawn);
}

