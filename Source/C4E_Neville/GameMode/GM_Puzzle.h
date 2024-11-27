#pragma once

#include "CoreMinimal.h"
#include "C4E_Neville/Guys/P_Guy.h"
#include "C4E_Neville/Interface/GameRuleReturns.h"
#include "GameFramework/GameMode.h"
#include "GM_Puzzle.generated.h"

class ALevelManager;
class APC_Guy;
class AP_Guy;

UCLASS(Abstract)
class C4E_NEVILLE_API AGM_Puzzle : public AGameMode, public IGameRuleReturns
{
	GENERATED_BODY()

public:
	AGM_Puzzle();

	//Designers may call these
	UFUNCTION(BlueprintCallable)
	void FailLevel();
	UFUNCTION(BlueprintCallable)
	void EndLevel();

	//Designers may not call these
	UFUNCTION()
	void Handle_CandyGameRuleComplete();
	UFUNCTION()
	void Handle_TimerGameRuleComplete();
	UFUNCTION()
	void Handle_PumpkinGameRuleComplete();
	UFUNCTION()
	void PlayerOutOfLives(AP_Guy* guyThatDied);
	

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="_Important!")
	int _SharedLivesTotal;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Classes")
	TSubclassOf<ALevelManager> _LevelManagerClass;

	//Designers may find useful
	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<AActor>> _GuyStarts;
	UPROPERTY(BlueprintReadOnly)
	APC_Guy* _ControllerRef;
	UPROPERTY(BlueprintReadOnly)
	ALevelManager* _LevelManagerRef;
	UPROPERTY(BlueprintReadOnly)
	UGR_Candy* _CandyGRRef;
	UPROPERTY(BlueprintReadOnly)
	UGR_Pumpkin* _PumpkinGRRef;
	UPROPERTY(BlueprintReadOnly)
	bool _HasTimer;
	UPROPERTY(BlueprintReadWrite) //Made "ReadWrite" to ensure designers can add their own functionality
	int _GameRuleObjectivesToComplete;

	//Designers may call these
	UFUNCTION(BlueprintCallable)
	void EnableAllEndLevels();
	UFUNCTION(BlueprintCallable)
	void EndGame();
	UFUNCTION(BlueprintCallable)
	void CheckGameRuleObjectivesToComplete();

	//
	virtual UGR_Candy* GR_Candy_Ref_Implementation() override;
	virtual UGR_Pumpkin* GR_Pumpkin_Ref_Implementation() override;

	//Hooks
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Guys Spawned")
	void RecieveGuysSpawned(const TArray<AP_Guy*>& guys);
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Game Rule Setup")
	void RecieveGameRuleSetup();
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Controller Setup")
	void RecieveControllerSetup();
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Level Manager Setup")
	void RecieveLevelManagerSetup();
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Late Begin Play")
	void RecieveDelayedBeginPlay();
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Fail Level")
	void RecieveFailLevel();
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On End Level")
	void RecieveEndLevel();
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On End Game")
	void RecieveEndGame();
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Candy Game Rule Complete")
	void RecieveCandyGameRuleComplete();
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Pumpkin Game Rule Complete")
	void RecievePumpkinGameRuleComplete();
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Timer Game Rule Complete")
	void RecieveTimerGameRuleComplete();
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Player Out of Lives")
	void RecievePlayerOutOfLives(const AP_Guy* guyThatDied);

private:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	//Before "BeginPlay"
	virtual void HandleMatchIsWaitingToStart() override;
	//After "BeginPlay"
	void DelayedBeginPlay(bool played);
};