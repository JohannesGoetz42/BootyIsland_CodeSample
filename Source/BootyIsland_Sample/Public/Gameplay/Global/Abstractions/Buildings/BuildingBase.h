// Copyright Johannes Goetz

#pragma once

#include "Gameplay/Global/Enums/BuildingPreviewState.h"
#include "Gameplay/Global/Interfaces/HasSpawnLocationPicker.h"
#include "Gameplay/Global/Interfaces/HasCollisionBox.h"
#include "Gameplay/Global/Interfaces/MultiMesh.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingBase.generated.h"

UCLASS(Abstract)
/**
 * Base class for building actors
 */
class BOOTYISLAND_API ABuildingBase : public AActor, public IHasSpawnLocationPicker, public IHasCollisionBox, public IMultiMesh
{
	GENERATED_BODY()

public:

	ABuildingBase();

	UFUNCTION(BlueprintCallable)
		virtual const class UBuildingData* GetBuildingData() const { return nullptr; }

	FORCEINLINE FVector GetRoofTopLocation() const { return RoofTopLocation; }
	FORCEINLINE virtual class ATown* GetTown() const { return nullptr; }

	virtual void Setup(const class UBuildingData* BuildingData, class ATown* ParentTown) { return; }

	// Inherited via IHasSpawnLocationPicker
	FORCEINLINE virtual USpawnLocationPicker* GetSpawnLocationPicker() const { return SpawnLocationPicker; }

	// Inherited via IHasCollisionBox
	FORCEINLINE class UBoxComponent* GetCollisionBox() const override { return CollisionBox; }

	// Inherited via IMultimesh
	FORCEINLINE virtual UMeshComponent* GetMeshComponent() const override {
		checkNoEntry();
		return nullptr;
	}

protected:

	UPROPERTY(EditAnywhere)
		/* The collision box is used for simplified environment traces */
		class UBoxComponent* CollisionBox;

	/** Store the roof top location to allow components to place stuff on it */
	FVector RoofTopLocation;
	class USpawnLocationPicker* SpawnLocationPicker;

	// Inherited via IHasCollisionBox
	void UpdateCollisionBox(FBox BoundingBox) override;
};
