// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;

	// ...
}


/*// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}
*/

//Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if(!Barrel) return;
	if(!Turret) return;
	
	//Velocity, that will be set
	FVector OutLaunchVelocity;
	FVector StartPoint = Barrel->GetSocketLocation(TEXT("Projectile"));
	
	//Calculates an launch velocity for a projectile to hit a specified point.
	//This is done for precise shooting
	bool bHasAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		GetWorld(),
		OutLaunchVelocity,
		StartPoint,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
		);
	//Debugging shit
	//UE_LOG(LogTemp, Warning, TEXT("%s"), ( bHasAimSolution ? TEXT("true") : TEXT("false")));

	if(bHasAimSolution)
	{
		//Turns this OutLaunchVelocity vector to a normal vector (a unit vector, that equals to 1 with direction)
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		auto BarrelLocation = Barrel->GetComponentLocation();
		
		//Debugging shit
		/*auto ThisTank = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("This %s aiming at %s from %s"), *ThisTank, *AimDirection.ToString(), *BarrelLocation.ToString())*/
		
		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("At %f Aim solution is found"), Time)
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("At %f Aim solution is not found"), Time)
	}
	
}

void UTankAimingComponent::SetBarrelComponent(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretComponent(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//We need to keep BarrelRotation and TurretRotation separate from each other, because if we don't, turret rotation will be depending on barrel's rotation.
	//For example, if barrel looks down, turret will be moving opposite to its real direction, because its speed will be -1, like barrel's speed
	
	//Getting delta rotator between barrel forward vector and aim direction, turret forward vector and aim direction,
	//because to rotate them, we need delta vector, like in FindLookAtLocation()
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator TurretRotation = Turret->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	//These will get the right rotator for elevate and rotatte function. AimDirection, which we are looking now in game minus barrel's or turret's current rotation
	FRotator DeltaBarrelRotation = AimAsRotator - BarrelRotation;
	FRotator DeltaTurretRotation = AimAsRotator - TurretRotation;
	
	
	//Debugging shit
	/*APawn* PlayerPawn = Cast<APawn>(GetOwner());
	if(PlayerPawn->IsPlayerControlled())
	{
		UE_LOG(LogTemp, Warning, TEXT("AimAsRotator is %s"), *AimAsRotator.ToString())
		UE_LOG(LogTemp, Warning, TEXT("BarrelRotation is %s"), *BarrelRotation.ToString())
		UE_LOG(LogTemp, Warning, TEXT("DeltaRotation is %s"), *DeltaRotation.ToString())
	}*/
	
	//Elevating barrel up	
	//If pitch has minus value, speed will be -1
	//If pitch has plus value, speed will be +1
	Turret->Rotate(DeltaTurretRotation.Yaw);
	//Rotating turret	
	//If yaw has minus value, speed will be -1
	//If yaw has plus value, speed will be +1
	Barrel->Elevate(DeltaBarrelRotation.Pitch);
}
