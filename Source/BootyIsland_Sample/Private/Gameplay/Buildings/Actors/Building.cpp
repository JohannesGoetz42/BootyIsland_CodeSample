// Copyright Johannes Goetz

#include "Gameplay/Buildings/Actors/Building.h"
#include "Gameplay/Buildings/DataAssets/BuildingData.h"
#include "Gameplay/Buildings/Components/AISpawnLocationComponent.h"

#include "Gameplay/Global/Abstractions/AreaEffectComponent.h"
#include "Gameplay/Global/Abstractions/DataAssets/AreaEffectData.h"
#include "Gameplay/Global/Components/SpawnLocationPicker.h"
#include "Gameplay/Global/Interfaces/BuildingComponentData.h"
#include "Gameplay/Global/Factories/ComponentFactory.h"
#include "Gameplay/Global/Constants/CollisionChannels.h"
#include "Gameplay/Global/Helpers/CollisionHelper.h"

#include "Components/StaticMeshComponent.h" 
#include "Components/SkeletalMeshComponent.h" 
#include "Components/BoxComponent.h" 
#include "EngineUtils.h"

void ABuilding::Setup(const UBuildingData* BuildingData, class ATown* ParentTown)
{
	check(BuildingData);
	check(ParentTown);

	Town = ParentTown;
	DataAsset = BuildingData;

	SetupMesh();
	InitializeComponents();
}

void ABuilding::InitializeComponents()
{
	InitializeActorSpawnLocationComponents();

	for (UDataAsset* Component : DataAsset->Components)
	{
		if (IBuildingComponentData* ComponentData = Cast<IBuildingComponentData>(Component))
		{
			ComponentFactory::SpawnBuildingComponent(ComponentData->GetComponentClass(), this, ComponentData);
		}
	}
}

void ABuilding::InitializeActorSpawnLocationComponents()
{
	SpawnLocationPicker = NewObject<USpawnLocationPicker>(this, "Spawn Location Picker");
	SpawnLocationPicker->RegisterComponent();

	UAISpawnLocationComponent* AiSpawnLocationComponent = NewObject<UAISpawnLocationComponent>(this, "AI Spawn Location Component");
	AiSpawnLocationComponent->RegisterComponent();
	AiSpawnLocationComponent->AddToLocationPicker(SpawnLocationPicker);
}

void ABuilding::SetupMesh()
{
	if (!SpawnSkeletalOrStaticMesh())
	{
		return;
	}

	MeshComponent->RegisterComponent();
	MeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetCollisionResponseToChannel(COLLISION_LANDSCAPE, ECollisionResponse::ECR_Ignore);

	MeshComponent->bFillCollisionUnderneathForNavmesh = true;
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

bool ABuilding::SpawnSkeletalOrStaticMesh()
{
	if (!DataAsset->SkeletalMesh && !DataAsset->StaticMesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("Building data '%s' has no mesh!"), *DataAsset->GetName());
		return false;
	}

	FBox MeshBounds;
	if (DataAsset->SkeletalMesh)
	{
		USkeletalMeshComponent* SkeletalMeshComponent = NewObject<USkeletalMeshComponent>(this, "Skeletal Mesh");
		SkeletalMeshComponent->SetSkeletalMesh(DataAsset->SkeletalMesh);

		MeshBounds = SkeletalMeshComponent->SkeletalMesh->GetBounds().GetBox();
		MeshComponent = SkeletalMeshComponent;
	}
	else
	{
		UStaticMeshComponent* StaticMeshComponent = NewObject<UStaticMeshComponent>(this, "Skeletal Mesh");
		StaticMeshComponent->SetStaticMesh(DataAsset->StaticMesh);

		StaticMeshComponent->bUseDefaultCollision = true;
		MeshBounds = StaticMeshComponent->GetStaticMesh()->GetBoundingBox();
		MeshComponent = StaticMeshComponent;
	}

	UpdateCollisionBox(MeshBounds);
	return true;
}