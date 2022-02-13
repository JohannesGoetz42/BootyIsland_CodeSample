// Copyright Johannes Goetz

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RotationTool.generated.h"

UCLASS()
/**
 * PlayerTool for rotating a scene component
 */
class BOOTYISLAND_API URotationTool : public UActorComponent
{
	GENERATED_BODY()

public:	

	URotationTool();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetTargetComponent(USceneComponent* Component);
	void Deactivate() override;

protected:

	USceneComponent* TargetComponent;
	const class APlayerControllerBase* PlayerController;

	virtual void BeginPlay() override;
};
