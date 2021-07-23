// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
   GENERATED_BODY()
	
	//Getting player's tank
	ATank* PlayerTank = nullptr;

	//Acceptance radius to stop when moving to a player actor
	UPROPERTY(EditAnywhere, Category = "Pathfinding")
	float AcceptanceRadius = 8000.f;

	//Reference to aiming component for AimAt method
	UTankAimingComponent* AimCompRef;
	
public:

	void BeginPlay() override;

	//called when AI controller get posessed a tank
	void SetPawn(APawn* InPawn) override;
	
	void Tick(float DeltaTime) override;

	//Called when AI tank dies
	UFUNCTION()
	void OnPosessedTankDeath();
	
	ATankAIController();
};

