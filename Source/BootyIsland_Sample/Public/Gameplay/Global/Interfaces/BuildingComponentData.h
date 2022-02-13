// Copyright Johannes Goetz

#pragma once

// #include "Gameplay/Global/Interfaces/BuildingComponentData.h"

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BuildingComponentData.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UBuildingComponentData : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for building component data assets
 */
class BOOTYISLAND_API IBuildingComponentData
{
	GENERATED_BODY()

public:

	/** Get the component class for the respective data asset */
	virtual TSubclassOf<UActorComponent> GetComponentClass() const = 0;
};
