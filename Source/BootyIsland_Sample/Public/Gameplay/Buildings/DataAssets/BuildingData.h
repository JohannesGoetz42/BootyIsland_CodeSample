// Copyright Johannes Goetz

#pragma once

#include "Gameplay/Global/Interfaces/HasDisplayName.h"
#include "Gameplay/Global/Structs/TooltipItemStruct.h"
#include "Gameplay/Global/Helpers/ResourceHelper.h"

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BuildingData.generated.h"

/**
 * Data asset for buildings
 */
UCLASS(Abstract, BluePrintable, BluePrintType)
class BOOTYISLAND_API UBuildingData : public UDataAsset, public IHasDisplayName
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = "Appearance")
		/**
		* The static mesh of the building
		* Will not be used if a skeletal mesh is provided.
		*/
		UStaticMesh* StaticMesh;
	UPROPERTY(EditDefaultsOnly, Category = "Appearance")
		/**
		* The skeletal mesh of the building
		* Will be preferred over static mesh if both are provided.
		*/
		USkeletalMesh* SkeletalMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Behavior")
		TMap<TSubclassOf<class UResource>, int32> ResourceCost;
	UPROPERTY(EditDefaultsOnly, Instanced, BlueprintReadOnly, Category = "Behavior", meta = (MustImplement = "BuildingComponentData"))
		TArray<class UDataAsset*> Components;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GUI")
		UTexture2D* Thumbnail;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GUI")
		FText DisplayName = FText::FromString("PLACEHOLDER");
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GUI")
		FText TooltipText = FText::FromString("THIS TOOLTIP IS CURRENTLY UNDER CONSTRUCTION. AND SO PROBABLY IS IT'S FUNCTIONALITY.");

	UFUNCTION(BlueprintCallable)
		FTooltipItemStruct GetBuildingCostTooltip() { return ResourceHelper::MakeTooltipStruct(ResourceCost, FText::FromString("Material Cost")); }

	//Inherited via IHasDisplayName
	FORCEINLINE FText GetDisplayName() const override { return DisplayName; }
};
