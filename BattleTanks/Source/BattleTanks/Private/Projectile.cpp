// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Adding projectile movement component
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false;

	//Static mesh that will work like a static mesh idk why
	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);
	
	//Creating particle system comp
	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Launch Blast"));
	LaunchBlast->SetupAttachment(CollisionMesh);

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Impact Blast"));
	ImpactBlast->SetupAttachment(CollisionMesh);
	ImpactBlast->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(TEXT("Explosion Force"));
	ExplosionForce->SetupAttachment(CollisionMesh);

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (!ensure(LaunchBlast && ImpactBlast)) return;
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	ExplosionForce->FireImpulse();

	//We can't just destroy the root component, so we are just reasigning it to other component to destroy it
	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();

	//Actual projectile destroy timer
	FTimerHandle ProjectileDestroy;

	GetWorld()->GetTimerManager().SetTimer(ProjectileDestroy, this, &AProjectile::OnTimerExpire, DestroyDelay, false);
}

void AProjectile::OnTimerExpire()
{
	Destroy();
}

void AProjectile::LaunchProjectile(float Speed)
{
	//Sets the velocity to the new value, rotated into Actor space.
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	//Not sure what it is, check it out, ok?
	ProjectileMovement->Activate();
}

