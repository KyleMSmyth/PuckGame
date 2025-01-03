// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "../PlayerController/PuckGamePlayerController.h"
#include "PuckGameCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class APuckGameCharacter : public ACharacter
{
	GENERATED_BODY()

	//Removing player camera in order to implement shared Bird's Eye Camera
	//
	//	///** Camera boom positioning the camera behind the character */
	//	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//	//USpringArmComponent* CameraBoom;
	//
	//	///** Follow camera */
	//	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//	//UCameraComponent* FollowCamera;
	//
	//////////////////////////////


public:
	APuckGameCharacter();
	
		/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	UFUNCTION()
	void AttachPuck(class APuck* puck);

	UFUNCTION()
	void DetachPuck();

	UFUNCTION()
	void ChargeShot();

	UFUNCTION()
	void Shoot();

	UFUNCTION()
	void FlipPuck();

	UFUNCTION()
	void FlipStart();

	UFUNCTION()
	void FlipCancel();

	UFUNCTION()
	void Sprint();

	UFUNCTION()
	void StopSprint();

	UFUNCTION()
	void BodyCheck();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


	UPROPERTY()
	class APuckGamePlayerController* m_controller;

protected:
	class APuck* m_attachedPuck;

	float m_chargeRate;
	float m_shotPower;
	
	float m_checkingForce;

	UPROPERTY(EditDefaultsOnly)
	float m_baseShotPower;
	bool m_bIsCharging;
	bool m_flipCharging;


	UPROPERTY()
	FVector m_flipStartPos;

	UPROPERTY()
	FRotator m_flipDelta;

	UPROPERTY()
	FRotator m_flipStartRot;

	UPROPERTY(EditDefaultsOnly)
	float m_flipWait = 0.0f;



	FTimerHandle m_staminaCoolDown;
	FTimerHandle m_staminaRefill;

	bool m_bIsHustle ;
	bool m_bIsChecking;

	void RefillStamima();

	bool DrainStamina(float amount);


	UPROPERTY(EditDefaultsOnly)
	float m_baseSpeed;

	UPROPERTY(EditDefaultsOnly)
	float m_baseAccel;

	UPROPERTY(EditDefaultsOnly)
	float m_sprintSpeed;

	UPROPERTY(EditDefaultsOnly)
	float m_sprintAccel;

	UPROPERTY(EditDefaultsOnly)
	float m_maxStamina = 100.0f;

	UPROPERTY()
	float m_stamina;
	
	UPROPERTY()
	float m_staminaDelay = 3.0f;

	UPROPERTY()
	float m_staminaRechargeRate = 33.33f;

	UPROPERTY()
	float m_staminaUseRate = 50.0f;

	UPROPERTY()
	float m_staminaDeltaTime = 0.0f;

	UPROPERTY()
	float m_checkingDeltaTime = 0.0f;

	UPROPERTY()
	float m_checkingCooldown = 2.0f;





protected:


	
	// To add mapping context
	virtual void BeginPlay();

	virtual void Tick(float DeltaTime);

public:
	///** Returns CameraBoom subobject **/
	//FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	///** Returns FollowCamera subobject **/
	//FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

