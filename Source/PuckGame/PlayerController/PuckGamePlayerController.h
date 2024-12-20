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

protected:
	virtual void SetupInputComponent() override;
	virtual void AcknowledgePossession(APawn* pawn) override;
	virtual void BeginPlay() override;


	void Move(const FInputActionValue& value);

	void Look(const FInputActionValue& value);

	void Jump();

	void StartShooting();
	void StopShooting();


	void StopJumping();

private:
	class APuckGameCharacter* m_character;

};
