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
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();
	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

};
