// Fill out your copyright notice in the Description page of Project Settings.


#include "Puck.h"
#include "Components/BoxComponent.h"
#include "PuckGame/Character/PuckGameCharacter.h"

// Sets default values
APuck::APuck()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(m_mesh);


	m_mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	m_mesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	m_mesh->SetCollisionProfileName("Mesh");
	m_mesh->SetSimulatePhysics(true);
	m_mesh->SetupAttachment(RootComponent);

	m_mesh->OnComponentHit.AddDynamic(this, &APuck::OnActorHit);

	m_offset = 200.0f;
}

void APuck::DetachCharacter(FVector OptionalForce)
{
	m_attachedCharacter = nullptr;

	m_mesh->SetSimulatePhysics(true);

	GetMesh()->AddImpulse(OptionalForce);

}

// Called when the game starts or when spawned
void APuck::BeginPlay()
{
	Super::BeginPlay();
	
}

void APuck::OnActorHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor == Cast<APuckGameCharacter>(OtherActor))
	{
		m_attachedCharacter = Cast<APuckGameCharacter>(OtherActor);
		m_attachedCharacter->AttachPuck(this);
		m_mesh->SetWorldRotation(FRotator::ZeroRotator);
		m_mesh->SetSimulatePhysics(false);
	}
}

// Called every frame
void APuck::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(m_attachedCharacter)
		SetActorLocation(m_attachedCharacter->GetActorLocation() + m_attachedCharacter->GetActorForwardVector().GetSafeNormal() * m_offset);

}



