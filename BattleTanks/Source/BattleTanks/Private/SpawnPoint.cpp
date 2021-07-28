// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPoint.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USpawnPoint::USpawnPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	/*From the documents 31 of AttachToComponent():
    
    “It is valid to call this on components whether or not they have been Registered, however from constructor or when not registered it is preferable to use SetupAttachment.”*/

	//We need to do it, because BeginPlay() in SprungWheel invokes first, than the spawning action.
	//Spawns given class and returns class T pointer, forcibly sets world transform (note this allows scale as well).
	SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>(ActorToSpawn, GetComponentTransform());
	if(!SpawnedActor) return;
	SpawnedActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	
	//Called to finish the spawning process, generally in the case of deferred spawning
	UGameplayStatics::FinishSpawningActor(SpawnedActor, GetComponentTransform());
	
	
}


// Called every frame
void USpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

