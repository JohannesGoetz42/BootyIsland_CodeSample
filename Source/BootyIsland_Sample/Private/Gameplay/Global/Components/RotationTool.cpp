// Copyright Johannes Goetz

#include "Gameplay/Global/Components/RotationTool.h"
#include "Gameplay/Global/Abstractions/Player/PlayerControllerBase.h"
#include "Gameplay/Global/Abstractions/Buildings/BuildingBase.h"

#include "Components/PrimitiveComponent.h"

URotationTool::URotationTool() : Super()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void URotationTool::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerControllerBase>(GetOwner());
	check(PlayerController);
}

void URotationTool::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	check(IsValid(TargetComponent));

	FVector CursorWorldLocation;
	if (!PlayerController->TryGetCursorWorldLocation(CursorWorldLocation))
	{
		return;
	}

	FVector CurrentVector = TargetComponent->GetComponentLocation() - CursorWorldLocation;
	float NewAngle = /*atan2 of forward vector is 0, so there is no need to calculate*/ -FMath::Atan2(CurrentVector.X, CurrentVector.Y);
	NewAngle = FMath::RadiansToDegrees(NewAngle);

	TargetComponent->SetRelativeRotation(FRotator(0, NewAngle, 0));
}

void URotationTool::SetTargetComponent(USceneComponent* Component)
{
	check(IsValid(Component));
	TargetComponent = Component;
	Activate();
}

void URotationTool::Deactivate()
{
	Super::Deactivate();
	TargetComponent = nullptr;
}