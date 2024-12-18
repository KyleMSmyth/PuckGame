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
protected:


			

protected:


	
	// To add mapping context
	virtual void BeginPlay();

public:
	///** Returns CameraBoom subobject **/
	//FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	///** Returns FollowCamera subobject **/
	//FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
