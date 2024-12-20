// Copyright Epic Games, Inc. All Rights Reserved.

#include "PuckGameCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "PuckGame/Puck/Puck.h"


DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// APuckGameCharacter

APuckGameCharacter::APuckGameCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Character moves in the direction of input...
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 350;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	m_chargeRate = 75000.0f;
	m_bIsCharging = false;
	m_baseShotPower = 5000.0f;
	m_shotPower = m_baseShotPower;

	m_controller = Cast<APuckGamePlayerController>(Controller);

	//// Create a camera boom (pulls in towards the player if there is a collision)
	//CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//CameraBoom->SetupAttachment(RootComponent);
	//CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	//CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	//// Create a follow camera
	//FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	//FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	//FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void APuckGameCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

}

void APuckGameCharacter::Tick(float DeltaTime)
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::SanitizeFloat(m_shotPower));

	FHitResult Hit;

	m_controller->GetHitResultUnderCursor(ECC_WorldStatic, true, Hit);

	FVector Direction = GetActorLocation() - Hit.Location;

	//FVector mouseLocation, mouseDirection;
	FRotator currentCharacterRotation = this->GetActorRotation();
	FRotator targetRotation = Direction.Rotation();

	FRotator newRotation = FRotator(currentCharacterRotation.Pitch, targetRotation.Yaw, currentCharacterRotation.Roll);
	SetActorRotation(newRotation);

	if(m_bIsCharging)
		m_shotPower = FMath::Clamp(m_shotPower + (m_chargeRate * GetWorld()->GetDeltaSeconds()), 0.0f, 100000.0f);
}



void APuckGameCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		APlayerCameraManager* CamManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;

		const FVector ForwardMovement = FVector(CamManager->GetTransformComponent()->GetForwardVector().X, 
											CamManager->GetTransformComponent()->GetForwardVector().Y,0);

		const FVector RightMovement = FVector(CamManager->GetTransformComponent()->GetRightVector().X,
											CamManager->GetTransformComponent()->GetRightVector().Y, 0);
		
		//
		//// find out which way is forward
		//const FRotator Rotation = Controller->GetControlRotation();
		//const FRotator YawRotation(0, Rotation.Yaw, 0);

		//// get forward vector
		//const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		//// get right vector 
		//const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardMovement.GetSafeNormal(), MovementVector.Y);
		AddMovementInput(RightMovement.GetSafeNormal(), MovementVector.X);
	}
}

void APuckGameCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APuckGameCharacter::AttachPuck(APuck* puck)
{
	m_attachedPuck = puck;
}

void APuckGameCharacter::DetachPuck()
{
	if(m_attachedPuck)
	{
		//m_attachedPuck->DetachCharacter();
		m_attachedPuck = nullptr;
	}
}

void APuckGameCharacter::ChargeShot()
{
	if(Controller != nullptr)
	{
		if (m_attachedPuck)
		{
			m_bIsCharging = true;
		}
	}
}

void APuckGameCharacter::Shoot()
{
	if(Controller != nullptr)
	{
		if (m_attachedPuck)
		{
			m_bIsCharging = false;
			m_attachedPuck->DetachCharacter((GetActorForwardVector().GetSafeNormal() * m_shotPower));

			DetachPuck();
			m_shotPower = m_baseShotPower;
			
		}
	}
}
