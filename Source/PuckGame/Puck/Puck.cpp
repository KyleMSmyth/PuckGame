// Fill out your copyright notice in the Description page of Project Settings.


#include "Puck.h"
#include "Components/BoxComponent.h"
#include "PuckGame/Character/PuckGameCharacter.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APuck::APuck()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(m_mesh);


	m_mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	m_mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	m_mesh->SetCollisionProfileName("BlockAllDynamic");
	//m_mesh->SetCollisionProfileName(ecollisionprofile)
	//m_mesh->SetCollisionProfileName("Mesh");
	m_mesh->SetSimulatePhysics(true);
	m_mesh->SetGenerateOverlapEvents(true);
	m_mesh->SetupAttachment(RootComponent);
	m_mesh->BodyInstance.bLockXRotation = true;
	m_mesh->BodyInstance.bLockYRotation = true;

	m_mesh->OnComponentHit.AddDynamic(this, &APuck::OnActorHit);
	m_mesh->OnComponentBeginOverlap.AddDynamic(this, &APuck::OnBeginOverlap);

	m_offset = 200.0f;
}

void APuck::DetachCharacter(FVector OptionalForce)
{
	m_attachedCharacter = nullptr;



	m_mesh->SetSimulatePhysics(true);
	m_mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	m_mesh->SetCollisionProfileName("BlockAllDynamic");

	//m_mesh->SetEnableGravity(true);
	//m_mesh->BodyInstance.bLockXRotation = false;
	//m_mesh->BodyInstance.bLockYRotation = false;

	m_mesh->ComponentVelocity = FVector::ZeroVector;
	SetActorRotation(FRotator::ZeroRotator);

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
		m_mesh->SetSimulatePhysics(false);
		m_mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		m_mesh->SetCollisionProfileName("OverlapAllDynamic");
		m_mesh->SetGenerateOverlapEvents(true);

		m_attachedCharacter = Cast<APuckGameCharacter>(OtherActor);
		m_attachedCharacter->AttachPuck(this);

		//m_mesh->SetEnableGravity(false);

		//m_mesh->ComponentVelocity = FVector::ZeroVector;
		//SetActorRotation(FRotator::ZeroRotator);
	}
}

void APuck::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (m_attachedCharacter)
	{
		if (OtherActor == Cast<APuckGameCharacter>(OtherActor))
		{
			if(OtherActor != m_attachedCharacter)
				DetachCharacter();
		}
	}
}

// Called every frame
void APuck::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(m_attachedCharacter)
	{
		SetActorLocation(m_attachedCharacter->GetActorLocation() + m_attachedCharacter->GetActorForwardVector().GetSafeNormal() * m_offset);
	}

}



