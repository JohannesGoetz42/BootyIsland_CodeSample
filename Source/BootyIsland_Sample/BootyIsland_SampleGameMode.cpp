// Copyright Epic Games, Inc. All Rights Reserved.

#include "BootyIsland_SampleGameMode.h"
#include "BootyIsland_SampleCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABootyIsland_SampleGameMode::ABootyIsland_SampleGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
