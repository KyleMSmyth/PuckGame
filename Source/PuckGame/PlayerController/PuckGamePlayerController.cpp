// Fill out your copyright notice in the Description page of Project Settings.


#include "PuckGamePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LocalPlayer.h"


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

		//Flipping Puck
		Component->BindAction(m_flipAction, ETriggerEvent::Started, this, &APuckGamePlayerController::FlipStart);
		Component->BindAction(m_flipAction, ETriggerEvent::Completed, this, &APuckGamePlayerController::FlipCancel);

		//Sprinting
		Component->BindAction(m_sprintAction, ETriggerEvent::Started, this, &APuckGamePlayerController::StartSprint);
		Component->BindAction(m_sprintAction, ETriggerEvent::Completed, this, &APuckGamePlayerController::StopSprint);

		// Moving
		Component->BindAction(m_moveAction, ETriggerEvent::Triggered, this, &APuckGamePlayerController::Move);

		// Looking
		Component->BindAction(m_lookAction, ETriggerEvent::Triggered, this, &APuckGamePlayerController::Look);

		//BodyChecking
		Component->BindAction(m_checkAction, ETriggerEvent::Triggered, this, &APuckGamePlayerController::BodyCheck);

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

void APuckGamePlayerController::BodyCheck()
{
	if (!m_character) return;

	m_character->BodyCheck();
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

void APuckGamePlayerController::FlipStart()
{
	if (!m_character) return;

	m_character->FlipStart();
}

void APuckGamePlayerController::FlipCancel()
{
	if (!m_character) return;

	m_character->FlipCancel();
}

void APuckGamePlayerController::StopJumping()
{
	if (!m_character) return;

	m_character->StopJumping();
}

void APuckGamePlayerController::StartSprint()
{
	if (!m_character) return;

	m_character->Sprint();
}

void APuckGamePlayerController::StopSprint()
{
	if (!m_character) return;

	m_character->StopSprint();

}

void APuckGamePlayerController::AcknowledgePossession(APawn* pawn)
{
	APlayerController::AcknowledgePossession(pawn);

	m_character = Cast<APuckGameCharacter>(pawn);

	m_character->Controller = this;

	m_character->m_controller = this;

	
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

	bShowMouseCursor = true;
	

	// Setup input components for minigame controls create in begin play.
	UEnhancedInputComponent* comp = Cast<UEnhancedInputComponent>(InputComponent);
	if (!comp) return;
}

bool APuckGamePlayerController::GetHitResultUnderCursor(ECollisionChannel TraceChannel, bool bTraceComplex, FHitResult& HitResult) const
{
	ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player);
	bool bHit = false;
	if (LocalPlayer && LocalPlayer->ViewportClient)
	{
		FVector2D MousePosition;
		if (LocalPlayer->ViewportClient->GetMousePosition(MousePosition))
		{
			bHit = GetHitResultAtScreenPosition(MousePosition, TraceChannel, bTraceComplex, HitResult);
		}
	}

	if (!bHit)	//If there was no hit we reset the results. This is redundant but helps Blueprint users
	{
		HitResult = FHitResult();
	}

	return bHit;
}

