// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SpawnPoint.generated.h"

//Used for spawning spring

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANKS_API USpawnPoint : public USceneComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Spawn Spring")
	TSubclassOf<AActor> ActorToSpawn;
	
public:	
	// Sets default values for this component's properties
	USpawnPoint();
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	


		
};
