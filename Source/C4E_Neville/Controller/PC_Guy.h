#pragma once

#include "CoreMinimal.h"
#include "C4E_Neville/Guys/P_Guy.h"
#include "GameFramework/PlayerController.h"
#include "PC_Guy.generated.h"

class UW_Hud;
class AGuyStart;
struct FInputActionValue;
class UInputAction;
class AP_Guy;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOutOfLivesAlertSignature, AP_Guy*, guy);

UCLASS(Abstract)
class C4E_NEVILLE_API APC_Guy : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SwapCharacter();
	UFUNCTION(BlueprintCallable)
	void ControllerSetup(TArray<TSubclassOf<AP_Guy>> swapOrder, TArray<AP_Guy*> guys, int sharedLivesTotal, bool bigGuyCanThrow);
	UFUNCTION()
	void RespawnCheck(AP_Guy* guy);

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
	void Move(const FInputActionValue& value);
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
};