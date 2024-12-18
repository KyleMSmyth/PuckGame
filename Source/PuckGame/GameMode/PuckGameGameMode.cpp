// Copyright Epic Games, Inc. All Rights Reserved.

#include "PuckGameGameMode.h"
#include "../Character/PuckGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

APuckGameGameMode::APuckGameGameMode()
{
	// set default pawn class to our Blueprinted character
	if (PlayerPawnBPClass != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass;
	}
}
