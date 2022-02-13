// Copyright Johannes Goetz

#pragma once

#include "Gameplay/Global/Enums/BuildingPreviewState.h"
#include "Gameplay/Global/Interfaces/HasCollisionBox.h"
#include "Gameplay/Global/Interfaces/MultiMesh.h"
#include "Gameplay/Global/Interfaces/ToolPreview.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingPreview.generated.h"

DECLARE_MULTICAST_DELEGATE(FBuildingPreviewChangedSignature)
DECLARE_MULTICAST_DELEGATE_OneParam(FBuildingStateChangedSignature, EBuildingPreviewState);

UCLASS(Abstract, Blueprintable, BlueprintType)
class BOOTYISLAND_API ABuildingPreview : public AActor, public IHasCollisionBox, public IMultiMesh, public IToolPreview
{
	GENERATED_BODY()

public:

	ABuildingPreview();

	/** Called when the preview building changes its state */
	FBuildingStateChangedSignature OnStateChanged;
	/** Called when new building data is assigned */
	FBuildingPreviewChangedSignature OnPreviewChanged;

	UFUNCTION()
		void UpdatePreviewedBuilding(const class UBuildingData* NewBuildingData);

	EBuildingPreviewState GetPreviewState() const;
	FORCEINLINE UMeshComponent* GetMeshComponent() const override { return MeshComponent; }
	FORCEINLINE class UBoxComponent* GetCollisionBox() const override { return CollisionBox; }
	FORCEINLINE const class UBuildingData* GetBuildingData() const { return BuildingData; }

protected:

	UPROPERTY(EditAnywhere, meta = (MustImplement = "PreviewComponent"))
		/** The building components this tool applies to preview buildings */
		TArray<TSubclassOf<UActorComponent>> PreviewComponents;

	UPROPERTY(EditAnywhere)
		class UPreviewStateManager* StateManager;
	UPROPERTY(EditAnywhere)
		class UBoxComponent* CollisionBox;

	const class UBuildingData* BuildingData;
	UStaticMeshComponent* MeshComponent;

	virtual void BeginPlay() override;
	void InitializePreviewComponents();
};
