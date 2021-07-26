// Fill out your copyright notice in the Description page of Project Settings.


#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mass = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mass"));
	RootComponent = Mass;

	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel"));
	Wheel->SetupAttachment(Mass);

	PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("PhysicsConstraint"));
	PhysicsConstraint->SetupAttachment(Mass);
	
	

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

