#pragma once

#include "CoreMinimal.h"
#include "C4E_Neville/Guys/P_Guy.h"
#include "C4E_Neville/Interface/GuyController.h"
#include "GameFramework/PlayerController.h"
#include "PC_Guy.generated.h"

class AP_Guy_Big;
class UW_Hud;
class AGuyStart;
struct FInputActionValue;
class UInputAction;
class AP_Guy;

USTRUCT(BlueprintType)
struct FGuyData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AP_Guy* _Guy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _CanSpecial;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOutOfLivesAlertSignature, AP_Guy*, guy);

UCLASS(Abstract)
class C4E_NEVILLE_API APC_Guy : public APlayerController, public IGuyController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SwapCharacter();
	UFUNCTION(BlueprintCallable)
	void ControllerSetup(TArray<FGuyData> guys, int sharedLivesTotal);
	void UISetupAlert(int maxCandy, int maxPumpkin, bool hasTimer);

	virtual FGenericTeamId GetGenericTeamId() const override;

	FGenericTeamId _TeamID = FGenericTeamId(2);
	
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
	TArray<AP_Guy*> _GuyList;

protected: //Hud
	UPROPERTY(EditAnywhere)
	TSubclassOf<UW_Hud> _HudWidgetClass;
	TObjectPtr<UW_Hud> _HudWidget;
	
private:
	bool _IsMoving;
	int _CurrentGuyIndex;
};