// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Puck.generated.h"

UCLASS()
class PUCKGAME_API APuck : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuck();

	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	class UStaticMeshComponent* m_mesh;

	UPROPERTY(EditDefaultsOnly, Category = "Overlap")
	class USphereComponent* m_sphere;

	UFUNCTION()
	class USphereComponent* GetSphere() { return m_sphere; }

	UFUNCTION()
	class UStaticMeshComponent* GetMesh() { return m_mesh; }

	UFUNCTION()
	class APuckGameCharacter* GetAttachedCharacter() { return m_attachedCharacter; }

	void DetachCharacter(FVector OptionalForce = FVector::ZeroVector);

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY()
	class APuckGameCharacter* m_attachedCharacter;

	UPROPERTY(EditDefaultsOnly)
	float m_offset;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
