// Copyright Johannes Goetz

#pragma once

// #include "Gameplay/Global/Interfaces/MultiMesh.h"

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MultiMesh.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMultiMesh : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for objects that can have a static XOR skeletal mesh
 */
class BOOTYISLAND_API IMultiMesh
{
	GENERATED_BODY()

public:

	virtual UMeshComponent* GetMeshComponent() const = 0;
};
