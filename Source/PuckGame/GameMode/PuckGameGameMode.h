// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PuckGameGameMode.generated.h"

UCLASS(minimalapi)
class APuckGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APuckGameGameMode();

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APawn> PlayerPawnBPClass;
};



