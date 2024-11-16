#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Hud.generated.h"

class UProgressBar;
class UTextBlock;

UCLASS()
class C4E_NEVILLE_API UW_Hud : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	void Setup(FString playerStartingLives, FString pumpkinTotal, FString candyTotal);

	void UpdateHealthBar();
	void UpdateCandyCounter(FString candyCurrent, FString candyMax);
	void UpdatePumpkinCounter(FString pumpkinCurrent, FString pumpkinMax);
	void UpdateTimerDisplay(FString current);
	void UpdatePlayerLivesDisplay(FString playerLivesCurrent, FString playerLivesMax);
	void UpdateLevelNameDisplay(FText levelNameDisplayText);
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CandyCounter;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> PumpkinCounter;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TimerDisplay;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> PlayerLivesDisplay;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> LevelNameDisplay;
};
