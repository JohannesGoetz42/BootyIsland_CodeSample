// Copyright Johannes Goetz

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HasCollisionBox.generated.h"

#define COLLISION_BOX_SIZE_MULTIPLIER 1.25f

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHasCollisionBox : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for objects that have a collision box
 * used for environment traces while keeping the default collision of the owner's mesh for physics simulation
 */
class BOOTYISLAND_API IHasCollisionBox
{
	GENERATED_BODY()

public:

	virtual class UBoxComponent* GetCollisionBox() const = 0;
	virtual void UpdateCollisionBox(FBox BoundingBox);
};
