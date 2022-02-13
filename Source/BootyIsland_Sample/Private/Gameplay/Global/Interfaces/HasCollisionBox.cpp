// Copyright Johannes Goetz

#include "Gameplay/Global/Interfaces/HasCollisionBox.h"

#include "Components/BoxComponent.h" 

// Add default functionality here for any IHasCollisionBox functions that are not pure virtual.

void IHasCollisionBox::UpdateCollisionBox(FBox BoundingBox)
{
	FVector UpscaledExtent = BoundingBox.GetExtent() * COLLISION_BOX_SIZE_MULTIPLIER;
	GetCollisionBox()->SetBoxExtent(UpscaledExtent);
}
