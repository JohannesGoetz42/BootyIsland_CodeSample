// Copyright Johannes Goetz

#pragma once

// #include "Gameplay/Global/Abstractions/Player/PlayerToolBase.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h" 
#include "PlayerToolBase.generated.h"

/**
 * Base class for player tools (Building, Selection, ...)
 */
UCLASS(Abstract)
class BOOTYISLAND_API UPlayerToolBase : public UActorComponent
{
	GENERATED_BODY()

public:

	/** Cancel the current tool action
	* Returns true if an action has been cancelled
	* Used to determine if cancel action should switch to default tool.
	*/
	virtual bool TryCancelAction() { return false; }
	virtual void OnToolActionPressed() { return; }
	virtual void OnToolActionReleased() { return; }
	virtual void OnSecondaryToolActionPressed() { return; }
	virtual void OnSecondaryToolActionReleased() { return; }
	virtual void Activate(bool bReset = false) override { Super::Activate(bReset); }
	virtual void Deactivate() override { Super::Deactivate(); }
	virtual void Setup(class APlayerControllerBase* Controller) {
		check(Controller);
		PlayerController = Controller;
	}

	const class APlayerControllerBase* GetPlayerController() { return PlayerController; }

protected:

	class APlayerControllerBase* PlayerController;
};
