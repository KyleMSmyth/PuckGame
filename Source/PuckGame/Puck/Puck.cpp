// Fill out your copyright notice in the Description page of Project Settings.


#include "Puck.h"
#include "Components/BoxComponent.h"
#include "PuckGame/Character/PuckGameCharacter.h"
#include "Components/SphereComponent.h"

// Sets default values
APuck::APuck()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//SetRootComponent(m_mesh);


	m_mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	m_mesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	m_mesh->SetCollisionProfileName("Mesh");
	m_mesh->SetSimulatePhysics(true);
	m_mesh->BodyInstance.bLockXRotation = true;
	m_mesh->BodyInstance.bLockYRotation = true;

	RootComponent = m_mesh;
	//m_mesh->SetupAttachment(RootComponent);

	//m_mesh->OnComponentHit.AddDynamic(this, &APuck::OnActorHit);

	m_sphere = CreateDefaultSubobject<USphereComponent>("Overlap");
	m_sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	m_sphere->SetGenerateOverlapEvents(true);
	m_sphere->SetCollisionProfileName("OverlapAll");
	m_sphere->InitSphereRadius(24.0f);
	m_sphere->bHiddenInGame = false;
	m_sphere->SetSimulatePhysics(false);
	m_sphere->SetupAttachment(RootComponent);


	m_offset = 150.0f;

	m_sphere->OnComponentBeginOverlap.AddDynamic(this, &APuck::OnBeginOverlap);
}

void APuck::DetachCharacter(FVector OptionalForce)
{
	m_attachedCharacter = nullptr;

	m_mesh->SetSimulatePhysics(true);

	GetMesh()->AddImpulse(OptionalForce);

}

void APuck::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (m_attachedCharacter)
	{
		if (OtherActor == Cast<APuckGameCharacter>(OtherActor))
		{
			if (OtherActor != m_attachedCharacter)
			{
				m_attachedCharacter->DetachPuck();
				DetachCharacter();
			}
		}
	}

	else if (OtherActor == Cast<APuckGameCharacter>(OtherActor))
	{
		m_attachedCharacter = Cast<APuckGameCharacter>(OtherActor);
		m_attachedCharacter->AttachPuck(this);
		m_mesh->SetWorldRotation(FRotator::ZeroRotator);
		m_mesh->SetSimulatePhysics(false);
	}
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



