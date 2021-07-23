// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "BattleTanks/Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.h"

ATankAIController::ATankAIController()
{
   // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
   PrimaryActorTick.bCanEverTick = true;
   PrimaryActorTick.bStartWithTickEnabled = true;
}

void ATankAIController::BeginPlay()
{
   Super::BeginPlay();
   //Getting Aiming Component
   AimCompRef = GetPawn()->FindComponentByClass<UTankAimingComponent>();
   //Getting player's tank
   PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}


void ATankAIController::Tick(float DeltaTime)
{
   Super::Tick(DeltaTime);
   //Don't know why we are doing it in tick, but in course it was like this. Maybe change it or smth.

   if(ensure(PlayerTank && AimCompRef))
   {
      MoveToActor(PlayerTank, AcceptanceRadius);
      AimCompRef->AimAt(PlayerTank->GetActorLocation());

      //TODO remove the firing limit mechanics
      if(AimCompRef->GetFiringState() == EFiringState::Locked)
      {
         AimCompRef->Fire();
      }
   }
}


void ATankAIController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);
    if(InPawn)
    {
       ATank* PosessedTank = Cast<ATank>(InPawn);
       if(!ensure(PosessedTank)) return;

       //Subscribe our local method to the tank's death event
       PosessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPosessedTankDeath);
    }
}

void ATankAIController::OnPosessedTankDeath()
{
   UE_LOG(LogTemp, Warning, TEXT("Received!"))
}
