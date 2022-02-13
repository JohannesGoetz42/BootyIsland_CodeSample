// Copyright Johannes Goetz


#include "Gameplay/Buildings/Components/BuildingTool.h"
#include "Gameplay/Buildings/DataAssets/BuildingData.h"
#include "Gameplay/Buildings/Actors/BuildingPreview.h"
#include "Gameplay/Buildings/Actors/Building.h"
#include "Gameplay/Buildings/Actors/Town.h"
#include "Gameplay/Buildings/Components/PreviewStateManager.h"
#include "Gameplay/Buildings/BuildingSpawner.h"

#include "Gameplay/Global/Components/RotationTool.h"
#include "Gameplay/Global/Abstractions/Player/PlayerControllerBase.h"
#include "Gameplay/Global/Abstractions/StorageBase.h"
#include "Gameplay/Global/Factories/ComponentFactory.h"
#include "Gameplay/Global/Enums/CursorState.h"

#include "Camera/CameraComponent.h" 
#include "EngineUtils.h"

UBuildingTool::UBuildingTool() : Super()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;

	ConstructorHelpers::FClassFinder<ABuildingPreview> DefaultPreview(TEXT("Class'/Game/Blueprints/Buildings/BP_BuildingPreview.BP_BuildingPreview_C'"));
	if (!DefaultPreview.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("Building tool could not load default preview asset!"));
		return;
	}

	PreviewClass = DefaultPreview.Class;
}

void UBuildingTool::BeginPlay()
{
	Super::BeginPlay();

	RotationTool = Cast<URotationTool>(PlayerController->GetComponentByClass(URotationTool::StaticClass()));
	check(RotationTool);
}

bool UBuildingTool::TryCancelAction()
{
	if (RotationTool->IsActive())
	{
		RotationTool->Deactivate();
		PlayerController->SetCursorState(ECursorState::CS_Build);
		bIsActionCancelled = true;
		return true;
	}

	return false;
}

void UBuildingTool::Deactivate()
{
	Super::Deactivate();

	SelectedBuildingAsset = nullptr;
	OnSelectedBuildingChanged.Broadcast(nullptr);

	if (IsValid(BuildingPreview))
	{
		BuildingPreview->Destroy();
	}

	BuildingPreview = nullptr;
}

void UBuildingTool::Activate(bool bReset)
{
	if (!SelectedBuildingAsset)
	{
		return;
	}

	APawn* Player = PlayerController->GetPawn();
	if (!IsValid(BuildingPreview))
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Instigator = Player;
		BuildingPreview = GetWorld()->SpawnActor<ABuildingPreview>(PreviewClass, SpawnParameters);
	}

	PlayerController->SetCursorState(ECursorState::CS_Build);

	Super::Activate(bReset);
}

void UBuildingTool::OnToolActionReleased()
{
	bIsActionCancelled = false;

	if (!IsToolActive())
	{
		return;
	}

	RotationTool->Deactivate();
	PlayerController->SetCursorState(ECursorState::CS_Build);

	ConfirmBuild();
}

void UBuildingTool::OnToolActionPressed()
{
	if (IsToolActive())
	{
		RotationTool->SetTargetComponent(BuildingPreview->GetRootComponent());
		PlayerController->SetCursorState(ECursorState::CS_Rotate);
	}
}

void UBuildingTool::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	FVector CursorWorldLocation;
	if (!RotationTool->IsActive() && PlayerController->TryGetCursorWorldLocation(CursorWorldLocation))
	{
		BuildingPreview->SetActorLocation(CursorWorldLocation);
	}
}

void UBuildingTool::SetSelectedBuilding(const UBuildingData* Building)
{
	check(Building);

	// if the selected building has not changed, do nothing
	if (SelectedBuildingAsset && SelectedBuildingAsset->GetClass() == Building->GetClass())
	{
		return;
	}

	SelectedBuildingAsset = Building;
	OnSelectedBuildingChanged.Broadcast(SelectedBuildingAsset);

	Activate();
}

void UBuildingTool::ConfirmBuild() const
{
	if (bIsActionCancelled || BuildingPreview->GetPreviewState() != EBuildingPreviewState::BS_Standard || !IsValid(PlayerController->GetCurrentTown()))
	{
		return;
	}

	IHasResourceStorage* ResourceStorage = PlayerController->GetCurrentTown();
	if (!ResourceStorage->GetStorage()->TryWithdrawResources(SelectedBuildingAsset->ResourceCost))
	{
		return;
	}

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Instigator = PlayerController->GetPawn();
	ABuildingBase* SpawnedBuilding = BuildingSpawner::SpawnBuilding(SelectedBuildingAsset, PlayerController->GetCurrentTown(), SpawnParameters, BuildingPreview->GetActorTransform());

	OnBuildingCreated.Broadcast(SpawnedBuilding);
}