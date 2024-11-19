#pragma once

#include "CoreMinimal.h"
#include "C4E_Neville/Guys/P_Guy.h"
#include "C4E_Neville/Interface/GuyController.h"
#include "GameFramework/PlayerController.h"
#include "PC_Guy.generated.h"

class UW_Hud;
class AGuyStart;
struct FInputActionValue;
class UInputAction;
class AP_Guy;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOutOfLivesAlertSignature, AP_Guy*, guy);

UCLASS(Abstract)
class C4E_NEVILLE_API APC_Guy : public APlayerController, public IGuyController
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SwapCharacter();
	UFUNCTION(BlueprintCallable)
	void ControllerSetup(TArray<TSubclassOf<AP_Guy>> swapOrder, TArray<AP_Guy*> guys, int sharedLivesTotal, bool bigGuyCanThrow);
	void UISetupAlert(int maxCandy, int maxPumpkin, bool hasTimer);

	virtual void UpdateTimerAlert_Implementation(float time) override;
	virtual void UpdateCandyAlert_Implementation(int current, int max) override;
	virtual void UpdatePumpkinAlert_Implementation(int current, int max) override;
	UFUNCTION()
	void RespawnCheck(AP_Guy* guy);
	UFUNCTION()
	void UpdateHealthAlert(float normalisedHealth, FLinearColor colour);

	int _SharedLivesCurrent;
	
	FOutOfLivesAlertSignature OnOutOfLives;

	
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
	void MovePressed();
	void Move(const FInputActionValue& value);
	void MoveReleased();
	void JumpPressed();
	void JumpReleased();
	void SpecialPressed();
	void CharacterSwapPressed();
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<TSubclassOf<AP_Guy>, AP_Guy*> _GuyMap;

protected: //Hud
	UPROPERTY(EditAnywhere)
	TSubclassOf<UW_Hud> _HudWidgetClass;
	TObjectPtr<UW_Hud> _HudWidget;
	
private:
	void GuySwapSetup(TArray<TSubclassOf<AP_Guy>> order, TArray<AP_Guy*> guys);

	bool _IsMoving;
};