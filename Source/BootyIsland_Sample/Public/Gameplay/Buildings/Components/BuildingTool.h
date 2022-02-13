// Copyright Johannes Goetz

#pragma once

#include "Gameplay/Global/Abstractions/Player/PlayerToolBase.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BuildingTool.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBuildingDelegate, const class UBuildingData*, NewBuilding);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBuildingCreatedDelegate, const class ABuildingBase*, NewBuilding);

/**
 * PlayerTool for creating buildings
 */
UCLASS(Abstract, Blueprintable)
class BOOTYISLAND_API UBuildingTool : public UPlayerToolBase
{
	GENERATED_BODY()

public:

	UBuildingTool();

	UPROPERTY(BlueprintAssignable)
		FBuildingDelegate OnSelectedBuildingChanged;
	UPROPERTY(BlueprintAssignable)
		FBuildingCreatedDelegate OnBuildingCreated;

	UFUNCTION(BlueprintCallable)
		const class UBuildingData* GetSelectedBuildingAsset() const { return SelectedBuildingAsset; }
	UFUNCTION(BlueprintCallable)
		/** Set the selected building asset and update the preview */
		void SetSelectedBuilding(const class UBuildingData* Building);

	class ABuildingPreview* GetBuildingPreview() const { return BuildingPreview; }
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Inherited via UPlayerToolBase
	virtual bool TryCancelAction() override;
	virtual void Activate(bool bReset = false) override;
	virtual void Deactivate() override;
	virtual void OnToolActionReleased() override;
	virtual void OnToolActionPressed() override;

protected:

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ABuildingPreview> PreviewClass;

	/** Indicates that the current action is cancelled so the action key can be released. */
	bool bIsActionCancelled;
	/** The building asset currently selected for build */
	const class UBuildingData* SelectedBuildingAsset;
	/** The preview building */
	class ABuildingPreview* BuildingPreview;
	class URotationTool* RotationTool;

	void BeginPlay() override;
	void ConfirmBuild() const;
	bool IsToolActive() const { return IsComponentTickEnabled() && BuildingPreview && SelectedBuildingAsset; }
};
