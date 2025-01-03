// Fill out your copyright notice in the Description page of Project Settings.


#include "GoalVolume.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "../Puck/Puck.h"

// Sets default values
AGoalVolume::AGoalVolume()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_box = CreateDefaultSubobject<UBoxComponent>("Box");
	m_box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	m_box->SetCollisionProfileName("OverlapAll");
	m_box->SetSimulatePhysics(false);
	m_box->InitBoxExtent(m_boxSize);

	RootComponent = m_box;

	m_puck = nullptr;

	m_box->OnComponentBeginOverlap.AddDynamic(this, &AGoalVolume::OnBeginOverlap);
	m_box->OnComponentEndOverlap.AddDynamic(this, &AGoalVolume::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AGoalVolume::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGoalVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_bCheckGoal)
	{
		if (m_puck)
		{
			FVector Pos = m_puck->GetActorLocation();
			float Rad = m_puck->GetSphere()->GetScaledSphereRadius();

			// TO DO: Add functionality to check rotated goal
			if (Pos.X < GetActorLocation().X + (m_box->GetScaledBoxExtent().X- Rad)
				&& Pos.X > GetActorLocation().X - (m_box->GetScaledBoxExtent().X - Rad)
				&& Pos.Y < GetActorLocation().Y + (m_box->GetScaledBoxExtent().Y - Rad)
				&& Pos.Y > GetActorLocation().Y - (m_box->GetScaledBoxExtent().Y - Rad))
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString("goal"));

			}
		}
	}
}

void AGoalVolume::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == Cast<APuck>(OtherActor))
	{
		m_bCheckGoal = true;

		m_puck = Cast<APuck>(OtherActor);

		//FVector Pos = Puck->GetActorLocation();
		//float Rad = Puck->GetSphere()->GetScaledSphereRadius();
		//

		//if(Pos.X < GetActorLocation().X + ((m_box->GetScaledBoxExtent().X/2) - Rad)
		//	&& Pos.X > GetActorLocation().X - ((m_box->GetScaledBoxExtent().X / 2) + Rad)
		//		&& Pos.Y < GetActorLocation().Y + ((m_box->GetScaledBoxExtent().Y / 2) - Rad)
		//			&& Pos.Y > GetActorLocation().Y - ((m_box->GetScaledBoxExtent().Y / 2) + Rad))
		//{
		//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString("goal"));

		//}

	}

}

void AGoalVolume::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == Cast<APuck>(OtherActor))
	{
		m_bCheckGoal = false;

		m_puck = nullptr;
	}
}

