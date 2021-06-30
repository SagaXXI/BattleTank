// Fill out your copyright notice in the Description page of Project Settings.
//TODO fix the Tick() function 

#include "TankAIController.h"
#include "BattleTanks/Tank.h"
#include "Kismet/GameplayStatics.h"

ATankAIController::ATankAIController()
{
   // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
   PrimaryActorTick.bCanEverTick = true;
   PrimaryActorTick.bStartWithTickEnabled = true;
   
}

void ATankAIController::BeginPlay()
{
   Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
   Super::Tick(DeltaTime);
   //Don't know why we are doing it in tick, but in course it was like this. Maybe change it or smth.
   //6:42 in course
   //Getting controlled tank by this AI controller
   ATank* ControlledTank = Cast<ATank>(GetPawn());
   //Getting player's tank
   ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
   //Checking if AI tank is reloaded
   bool IsReloaded = (GetWorld()->GetTimeSeconds() - LastTimeFired) >= ReloadDelay;
   
   if(PlayerTank && IsReloaded)
   {
      ControlledTank->AimAt(PlayerTank->GetActorLocation());
      ControlledTank->Fire();

      //Last time AI tank fired
      LastTimeFired = GetWorld()->GetTimeSeconds();
   }
}
      