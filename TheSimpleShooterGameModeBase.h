// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TheSimpleShooterGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class THESIMPLESHOOTER_API ATheSimpleShooterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	virtual void PawnKilled(APawn* PawnKilled);
	
};
