// Fill out your copyright notice in the Description page of Project Settings.


#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	Suspension = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Suspension"));
	RootComponent = Suspension;
	
	/*From the documents 52 of SetupAttachment():

	“Generally intended to be called from its Owning Actor’s constructor and should be preferred over AttachToComponent when a component is not registered.”*/


	//Implementing wheel physics

	//Just need this for connecting between two constraints (suspension and wheel axle)
	Axle = CreateDefaultSubobject<USphereComponent>(TEXT("Axle"));
	Axle->SetupAttachment(Suspension);

	Wheel = CreateDefaultSubobject<USphereComponent>(TEXT("Wheel"));
	Wheel->SetupAttachment(Axle);
	Wheel->SetNotifyRigidBodyCollision(true);
	

	WheelAxle = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Wheel Axle"));
	WheelAxle->SetupAttachment(Axle);

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
	//Setting up constraints
	SetupConstraints();

	Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);
	
}
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->TickGroup == TG_PostPhysics)
	{
		TotalForceMagnitudeThisFrame = 0.f;
	}
	
}

void ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	ApplyForce();
}

void ASprungWheel::ApplyForce()
{
	Wheel->AddForce(Axle->GetForwardVector() * TotalForceMagnitudeThisFrame);
}

void ASprungWheel::SetupConstraints()
{
	//Getting Tank's Body comp for setting it to constraint comp
	if (!GetAttachParentActor()) return;
	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	
	//Setting constraint comps
	if (!BodyRoot || !Wheel) return;
	Suspension->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
	WheelAxle->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
	
}


void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	TotalForceMagnitudeThisFrame += ForceMagnitude;
}

