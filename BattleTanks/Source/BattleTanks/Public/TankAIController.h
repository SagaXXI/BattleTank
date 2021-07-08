// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
   GENERATED_BODY()

public:

   virtual void BeginPlay() override;

   virtual void Tick(float DeltaTime) override;
   
   ATankAIController();
	
private:

	//Reloading mechanics
	//Reloading delay for tank
	UPROPERTY(EditAnywhere)
	float ReloadDelay = 3.f;

	//When AI tank fired last time
	float LastTimeFired = 0.f;
	
	//Getting controlled tank by this AI controller
	ATank* ControlledTank = nullptr;
	//Getting player's tank
	ATank* PlayerTank = nullptr;

	//Acceptance radius to stop when moving to a player actor
	UPROPERTY(EditAnywhere, Category = "Pathfinding")
	float AcceptanceRadius = 3000.f;
   
};

