// Copyright Johannes Goetz

#pragma once

// #include "Gameplay/Global/Enums/BuildingPreviewState.h"

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EBuildingPreviewState : uint8 {
	BS_Standard UMETA(DisplayName = "Standard"),
	BS_Obstructed UMETA(DisplayName = "Obstructed"),
	BS_ResourcesUnavailable UMETA(DisplayName = "Resources Unavailable"),
	BS_InFogOfWar UMETA(DisplayName = "In Fog of War")
};