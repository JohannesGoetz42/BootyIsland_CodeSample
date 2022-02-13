// Copyright Johannes Goetz

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BuildingComponent.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBuildingComponent : public UInterface
{
	GENERATED_BODY()
};

/**
 * Marker interface for components that can be selected in building data assets
 */
class BOOTYISLAND_API IBuildingComponent
{
	GENERATED_BODY()
};
