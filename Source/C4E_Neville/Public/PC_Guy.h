#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PC_Guy.generated.h"

struct FInputActionValue;
class UInputAction;
/**
 * 
 */
UCLASS()
class C4E_NEVILLE_API APC_Guy : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, category = "Input")
	TObjectPtr<UInputAction> _LookAction;
	UPROPERTY(EditAnywhere, category = "Input")
	TObjectPtr<UInputAction> _MoveAction;
	UPROPERTY(EditAnywhere, category = "Input")
	TObjectPtr<UInputAction> _JumpAction;
	UPROPERTY(EditAnywhere, category = "Input")
	TObjectPtr<UInputAction> _SpecialAction;
	UPROPERTY(EditAnywhere, category = "Input")
	TObjectPtr<UInputAction> _CharacterSwapAction;

	
	virtual void SetupInputComponent() override;
	void Look(const FInputActionValue& value);
	void Move(const FInputActionValue& value);
	void JumpPressed();
	void JumpReleased();
	void SpecialPressed();
	void CharacterSwapPressed();
	virtual void OnPossess(APawn* InPawn) override;
};