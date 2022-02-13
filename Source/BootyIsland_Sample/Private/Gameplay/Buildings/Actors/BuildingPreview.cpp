// Copyright Johannes Goetz

#include "Gameplay/Buildings/Actors/BuildingPreview.h"
#include "Gameplay/Buildings/DataAssets/BuildingData.h"
#include "Gameplay/Buildings/Components/PreviewStateManager.h"
#include "Gameplay/Buildings/Components/BuildingTool.h"

#include "Gameplay/Global/Factories/ComponentFactory.h"
#include "Gameplay/Global/Helpers/CollisionHelper.h"

#include "Components/BoxComponent.h" 

// Sets default values
ABuildingPreview::ABuildingPreview() : Super()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComponent;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(FName("Collision Box"));
	CollisionBox->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CollisionHelper::Buildings::SetPreviewBuildingCollisionBehaviour(CollisionBox);

	StateManager = CreateDefaultSubobject<UPreviewStateManager>(FName("State Manager"));
}

void ABuildingPreview::UpdatePreviewedBuilding(const UBuildingData* NewBuildingData)
{
	if (!NewBuildingData)
	{
		OnStateChanged.Broadcast(EBuildingPreviewState::BS_Standard);
		OnPreviewChanged.Broadcast();
		return;
	}

	BuildingData = NewBuildingData;
	MeshComponent->SetStaticMesh(BuildingData->StaticMesh);

	FBox MeshBounds = MeshComponent->GetStaticMesh()->GetBounds().GetBox();
	UpdateCollisionBox(MeshBounds);

	OnPreviewChanged.Broadcast();
}

// Called when the game starts or when spawned
void ABuildingPreview::BeginPlay()
{
	Super::BeginPlay();

	UBuildingTool* BuildingTool = Cast<UBuildingTool>(GetInstigator()->GetController()->GetComponentByClass(UBuildingTool::StaticClass()));
	FScriptDelegate Delegate;
	Delegate.BindUFunction(this, FName("UpdatePreviewedBuilding"));
	BuildingTool->OnSelectedBuildingChanged.Add(Delegate);

	UpdatePreviewedBuilding(BuildingTool->GetSelectedBuildingAsset());

	InitializePreviewComponents();
	OnStateChanged.Broadcast(StateManager->GetPreviewState());
}

void ABuildingPreview::InitializePreviewComponents()
{
	for (TSubclassOf<UActorComponent> BuildingComponentClass : PreviewComponents)
	{
		if (BuildingComponentClass)
		{
			UActorComponent* SpawnedComponent = NewObject<UActorComponent>(this, BuildingComponentClass);
			SpawnedComponent->RegisterComponent();
		}
	}

	StateManager->TryUpdateState();
}

EBuildingPreviewState ABuildingPreview::GetPreviewState() const
{
	return StateManager->GetPreviewState();
}