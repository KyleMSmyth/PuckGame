// Fill out your copyright notice in the Description page of Project Settings.


#include "PuckGamePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"

#include "PuckGame/Character/PuckGameCharacter.h"


void APuckGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* Component = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Jumping
		Component->BindAction(m_jumpAction, ETriggerEvent::Started, this, &APuckGamePlayerController::Jump);
		Component->BindAction(m_jumpAction, ETriggerEvent::Completed, this, &APuckGamePlayerController::StopJumping);

		//Shooting
		Component->BindAction(m_shootAction, ETriggerEvent::Started, this, &APuckGamePlayerController::StartShooting);
		Component->BindAction(m_shootAction, ETriggerEvent::Completed, this, &APuckGamePlayerController::StopShooting);

		// Moving
		Component->BindAction(m_moveAction, ETriggerEvent::Triggered, this, &APuckGamePlayerController::Move);

		// Looking
		Component->BindAction(m_lookAction, ETriggerEvent::Triggered, this, &APuckGamePlayerController::Look);
	}

}

void APuckGamePlayerController::Move(const FInputActionValue& value)
{
	if (!m_character) return;

	m_character->Move(value);
}

void APuckGamePlayerController::Look(const FInputActionValue& value)
{
	if (!m_character) return;

	m_character->Look(value);
}

void APuckGamePlayerController::Jump()
{
	if (!m_character) return;

	m_character->Jump();
}

void APuckGamePlayerController::StartShooting()
{
	if (!m_character) return;

	m_character->ChargeShot();
}

void APuckGamePlayerController::StopShooting()
{
	if (!m_character) return;

	m_character->Shoot();
}

void APuckGamePlayerController::StopJumping()
{
	if (!m_character) return;

	m_character->StopJumping();
}

void APuckGamePlayerController::AcknowledgePossession(APawn* pawn)
{
	APlayerController::AcknowledgePossession(pawn);

	m_character = Cast<APuckGameCharacter>(pawn);

	
	//Player = m_character->getplater
}

void APuckGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(this))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if (m_mappingContext)
			{
				Subsystem->AddMappingContext(m_mappingContext, 0);
			}
		}
	}

	// Setup input components for minigame controls create in begin play.
	UEnhancedInputComponent* comp = Cast<UEnhancedInputComponent>(InputComponent);
	if (!comp) return;
}


