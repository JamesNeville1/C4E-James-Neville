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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Classes")
	TSubclassOf<ALevelManager> LevelManagerClass;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APC_Guy* _ControllerRef;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ALevelManager* _LevelManagerRef;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UGR_Candy* _CandyGRRef;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UGR_Pumpkin* _PumpkinGRRef;
	
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _BigGuyCanThrow = true;
	
	virtual AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName) override;
	void MyStartMatch(); //Used to spawn multiple characters used by player

	virtual void HandleMatchIsWaitingToStart() override;

	void EnableAllEndLevels();

	UFUNCTION()
	void EndGame();
	UFUNCTION()
	void EndLevel();
	UFUNCTION()
	void FailLevel(FString reason);
	UFUNCTION()
	void CandyGameRuleComplete();
	UFUNCTION()
	void TimerGameRuleComplete();
	UFUNCTION()
	void PumpkinGameRuleComplete();
	UFUNCTION()
	void PlayerOutOfLives(AP_Guy* guyThatDied);
	
	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual UGR_Candy* GR_Candy_Ref_Implementation() override;
	virtual UGR_Pumpkin* GR_Pumpkin_Ref_Implementation() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int sharedLivesTotal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<AP_Guy>> _SwapOrder;
	TArray<TObjectPtr<AActor>> _GuyStarts;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int _GameRuleObjectivesToComplete;

private:
	void CheckGameRuleObjectivesToComplete();
};
