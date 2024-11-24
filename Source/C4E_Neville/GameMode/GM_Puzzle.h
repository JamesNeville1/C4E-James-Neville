#pragma once

#include "CoreMinimal.h"
#include "C4E_Neville/Guys/P_Guy.h"
#include "C4E_Neville/Interface/GameRuleReturns.h"
#include "GameFramework/GameMode.h"
#include "GM_Puzzle.generated.h"

struct FGuyData;
class ALevelManager;
class APC_Guy;
class AP_Guy;

USTRUCT(BlueprintType)
struct FPreGuyData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AP_Guy> _Guy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool _CanSpecial;
};

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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="_Important!")
	TArray<FPreGuyData> _GuyData;
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
	
	virtual UGR_Candy* GR_Candy_Ref_Implementation() override;
	virtual UGR_Pumpkin* GR_Pumpkin_Ref_Implementation() override;

private:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

	//Before "BeginPlay"
	virtual void HandleMatchIsWaitingToStart() override;
	//After "BeginPlay"
	void DelayedBeginPlay(bool played);
};
