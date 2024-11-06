#pragma once

#include "CoreMinimal.h"
#include "C4E_Neville/Guys/P_Guy.h"
#include "C4E_Neville/Interface/GameRuleReturns.h"
#include "GameFramework/GameMode.h"
#include "GM_Puzzle.generated.h"

class APC_Guy;
class AP_Guy;

UCLASS(Abstract)
class C4E_NEVILLE_API AGM_Puzzle : public AGameMode, public IGameRuleReturns
{
	GENERATED_BODY()

public:
	AGM_Puzzle();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APC_Guy* _ControllerRef;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UGR_Candy* _CandyGRRef;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UGR_Pumpkin* _PumpkinGRRef;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UGR_PlayerDeath* _PlayerDeathGRRef;
	
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	UFUNCTION()
	void CandyGameRuleComplete();
	UFUNCTION()
	void TimerGameRuleComplete();
	UFUNCTION()
	void PumpkinGameRuleComplete();
	UFUNCTION()
	void PlayerDeathGameRuleComplete();
	
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual UGR_Candy* GR_Candy_Ref_Implementation() override;
	virtual UGR_Pumpkin* GR_Pumpkin_Ref_Implementation() override;
	virtual UGR_PlayerDeath* GR_PlayerDeath_Ref_Implementation() override;
};
