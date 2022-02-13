// Copyright Johannes Goetz

#pragma once

// #include "Gameplay/Global/Interfaces/HasSpawnLocationPicker.h"

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HasSpawnLocationPicker.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHasSpawnLocationPicker : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for objects that have a spawn location picker
 */
class BOOTYISLAND_API IHasSpawnLocationPicker
{
	GENERATED_BODY()

public:

	virtual class USpawnLocationPicker* GetSpawnLocationPicker() const = 0;
};
