// Copyright Johannes Goetz

#pragma once

#include "Gameplay/Global/Abstractions/Buildings/BuildingBase.h"
#include "Gameplay/Global/Enums/BuildingPreviewState.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Building.generated.h"

UCLASS()
class BOOTYISLAND_API ABuilding : public ABuildingBase
{
	GENERATED_BODY()

public:

	FORCEINLINE UMeshComponent* GetMeshComponent() const override { return MeshComponent; }
	FORCEINLINE const class UBuildingData* GetBuildingData() const override { return DataAsset; }

	/** Get the town this building belongs to */
	class ATown* GetTown() const override { return Town; }


protected:

	UPROPERTY(EditAnywhere)
		UMeshComponent* MeshComponent;

	/** The town this building belongs to */
	class ATown* Town;
	const class UBuildingData* DataAsset;

	/** Initialize the components from the data asset. */
	void InitializeComponents();
	void InitializeActorSpawnLocationComponents();
	void SetupMesh();
	bool SpawnSkeletalOrStaticMesh();

	void Setup(const class UBuildingData* BuildingData, class ATown* ParentTown) override;
};