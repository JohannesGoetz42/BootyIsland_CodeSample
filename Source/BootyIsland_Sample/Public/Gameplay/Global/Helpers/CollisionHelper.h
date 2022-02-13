// Copyright Johannes Goetz

#pragma once

#include "Gameplay/Global/Constants/CollisionChannels.h"

namespace CollisionHelper
{
	namespace Buildings
	{
		void SetBuildingCollisionBehaviour(class UPrimitiveComponent* OutCollider);
		void SetPreviewBuildingCollisionBehaviour(class UPrimitiveComponent* OutCollider);
	}

	namespace Characters
	{
		void SetDeadCollisionBehaviour(class UPrimitiveComponent* OutCollider);
		void SetCharacterCollisionBehaviour(class UPrimitiveComponent* OutCollider);
	}

	namespace Landscape
	{
		FHitResult GetLandscapeHitCloseToLocation(UWorld* World, FVector Location, float TraceRange = 500.0f);
	}
};