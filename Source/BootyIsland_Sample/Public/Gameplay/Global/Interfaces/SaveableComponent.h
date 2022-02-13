// Copyright Johannes Goetz

#pragma once

// #include "Gameplay/Global/Interfaces/SaveableComponent.h"

#include "Gameplay/Global/Structs/ComponentSaveData.h"

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SaveableComponent.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USaveableComponent : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for components that have data to save
 */
class BOOTYISLAND_API ISaveableComponent
{
	GENERATED_BODY()

public:

	virtual FComponentSaveData GetSaveData() const = 0;
	virtual void SetSavedData(FComponentSaveData SaveData) = 0;
};
