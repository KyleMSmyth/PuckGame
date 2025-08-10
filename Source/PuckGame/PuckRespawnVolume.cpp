// Fill out your copyright notice in the Description page of Project Settings.


#include "PuckRespawnVolume.h"
#include "Components/BoxComponent.h"
#include "Puck/puck.h"

// Sets default values
APuckRespawnVolume::APuckRespawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_box = CreateDefaultSubobject<UBoxComponent>("Box");
	m_box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	m_box->SetCollisionProfileName("OverlapAll");
	m_box->SetSimulatePhysics(false);
	m_box->InitBoxExtent(m_boxSize);


	m_box->OnComponentBeginOverlap.AddDynamic(this, &APuckRespawnVolume::OnBeginOverlap);
	m_box->OnComponentEndOverlap.AddDynamic(this, &APuckRespawnVolume::OnOverlapEnd);
}

// Called when the game starts or when spawned
void APuckRespawnVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APuckRespawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APuckRespawnVolume::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == Cast<APuck>(OtherActor))
	{
		APuck* puck = Cast<APuck>(OtherActor);
		puck->ResetVelocity();
		puck->SetActorLocation(FVector(1425, 1705, 500));
	}
}

void APuckRespawnVolume::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}
