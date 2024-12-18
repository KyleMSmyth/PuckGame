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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
