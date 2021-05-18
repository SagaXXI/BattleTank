// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


/*// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}*/

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	/*auto BarrelLocation = Barrel->GetComponentLocation();
	UE_LOG(LogTemp, Warning, TEXT("This %s is aiming at %s from %s"), *ThisTank, *WorldSpaceAim.ToString(), *BarrelLocation.ToString())*/
	if(!Barrel) return;
	
	//Velocity, that will be set
	FVector OutLaunchVelocity;
	FVector StartPoint = Barrel->GetSocketLocation(TEXT("Projectile"));
	
	//Calculates an launch velocity for a projectile to hit a specified point.
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		GetWorld(),
		OutLaunchVelocity,
		StartPoint,
		HitLocation,
		LaunchSpeed,
		ESuggestProjVelocityTraceOption::DoNotTrace
		);
	if(bHaveAimSolution)
	{
		auto TankName = GetOwner()->GetName();
		//Turns this OutLaunchVelocity vector to a normal vector (a unit vector, that equals to 1 with direction)
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *TankName, *AimDirection.ToString())
		MoveBarrel(AimDirection);
		
	} 
	
	
}

void UTankAimingComponent::SetBarrelComponent(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator is %s"), *AimAsRotator.ToString())
	UE_LOG(LogTemp, Warning, TEXT("BarrelRotation is %s"), *BarrelRotation.ToString())
}