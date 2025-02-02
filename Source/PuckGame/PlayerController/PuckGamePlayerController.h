// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PuckGamePlayerController.generated.h"

/**
 * 
 */

class UInputAction;
struct FInputActionValue;
class UInputMappingContext;

UCLASS()
class PUCKGAME_API APuckGamePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* m_mappingContext;


	//Move Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* m_moveAction;

	//Look Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* m_lookAction;

	//Jump Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* m_jumpAction;

	//Shoot Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* m_shootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* m_flipAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* m_sprintAction;

	//BodyCheck Input Action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* m_checkAction;

	bool GetHitResultUnderCursor(ECollisionChannel TraceChannel, bool bTraceComplex, FHitResult& HitResult) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Device")
	bool m_bIsGamepad;

	bool DetermineInputDeviceDetails();

protected:
	virtual void SetupInputComponent() override;
	virtual void AcknowledgePossession(APawn* pawn) override;
	virtual void BeginPlay() override;


	void Move(const FInputActionValue& value);

	void Look(const FInputActionValue& value);

	void Jump();

	void BodyCheck();

	void StartShooting();
	void StopShooting();

	void FlipStart();
	void FlipCancel();

	void StopJumping();

	void StartSprint();
	void StopSprint();




	class UInputDeviceSubsystem* InputDeviceSubsystem;


private:
	class APuckGameCharacter* m_character;

};
