// Copyright Johannes Goetz

#include "Gameplay/Global/Abstractions/Buildings/BuildingBase.h"
#include "Gameplay/Global/Helpers/CollisionHelper.h"

#include "Components/BoxComponent.h" 

// Sets default values
ABuildingBase::ABuildingBase() : Super()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root Component");
	CollisionBox = CreateDefaultSubobject<UBoxComponent>("Collision Box");
	CollisionBox->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	CollisionHelper::Buildings::SetBuildingCollisionBehaviour(CollisionBox);
}

void ABuildingBase::UpdateCollisionBox(FBox BoundingBox)
{
	IHasCollisionBox::UpdateCollisionBox(BoundingBox);

	RoofTopLocation = GetActorLocation() + FVector(0, 0, BoundingBox.GetExtent().Z * 2);
}
