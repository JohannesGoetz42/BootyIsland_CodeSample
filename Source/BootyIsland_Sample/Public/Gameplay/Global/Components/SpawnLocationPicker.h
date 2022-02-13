// Copyright Johannes Goetz

#pragma once

#include "Gameplay/Global/Enums/SpawnLocationType.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpawnLocationPicker.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
/**
 * Manages spawn locations for various actors close to the owner actor
 */
class BOOTYISLAND_API USpawnLocationPicker : public UActorComponent
{
	GENERATED_BODY()

public:

	/** Get a random spawn location by type */
	FTransform GetSpawnLocation(ESpawnLocationType LocationType) const;
	void AddLocationData(class IHasSpawnLocation* LocationData, ESpawnLocationType LocationType) { SpawnLocationData.Add(LocationType, LocationData); }

protected:

	TMap<ESpawnLocationType, class IHasSpawnLocation*> SpawnLocationData = TMap<ESpawnLocationType, class IHasSpawnLocation*>();
};
