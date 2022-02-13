// Copyright Johannes Goetz

#pragma once

// #include "Gameplay/Global/Structs/ComponentSaveData.h"

#include "CoreMinimal.h"
#include "ComponentSaveData.generated.h"

USTRUCT()
struct FComponentSaveData
{
	GENERATED_BODY()

public:

	// OPTIMIZE: does redundand data cause large file sizes for savegames?
	UPROPERTY()
		TSubclassOf<UActorComponent> ComponentClass;
	UPROPERTY()
		TMap<TSubclassOf<class UPopulationType>, int32> PopulationData;
	UPROPERTY()
		TMap<TSubclassOf<class UResource>, int32> PrimaryResourceData;
	UPROPERTY()
		TMap<TSubclassOf<class UResource>, int32> SecondaryResourceData;
	UPROPERTY()
		bool PrimaryBool;
	UPROPERTY()
		bool SecondaryBool;
	UPROPERTY()
		float PrimaryFloat;
	UPROPERTY()
		float SecondaryFloat;
	UPROPERTY()
		float TertiaryFloat;
	UPROPERTY()
		TArray<FTransform> Transforms;
};