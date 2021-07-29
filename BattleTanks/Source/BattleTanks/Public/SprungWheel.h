// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class UPhysicsConstraintComponent;
class USphereComponent;

UCLASS()
class BATTLETANKS_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	USphereComponent* Wheel = nullptr;

	UPROPERTY(EditAnywhere)
	USphereComponent* Axle = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	UPhysicsConstraintComponent* Suspension = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UPhysicsConstraintComponent* WheelAxle = nullptr;

	//Setting up constraints
	void SetupConstraints();

	//Used to stop applying force when wheel is not hit with the floor
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//Variable which controls whether apply force or not
	float TotalForceMagnitudeThisFrame = 0.f;

	//Actual applying force
	void ApplyForce();
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();
	
	//Calculating and checking are we hitting the floor to apply the force (with the ForceMagnitudePerFrame variable)
	void AddDrivingForce(float ForceMagnitude);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float Deltatime) override;
	

};
