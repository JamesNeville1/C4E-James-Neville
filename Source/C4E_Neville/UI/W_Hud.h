﻿#pragma once

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

	void UpdateHealthBar(float normalisedHealth);
	void UpdateHealthBarColour(FLinearColor color);
	void UpdateCandyCounter(FString candyCurrent, FString candyMax);
	void UpdatePumpkinCounter(FString pumpkinCurrent, FString pumpkinMax);
	void UpdateTimerDisplay(FString current);
	void UpdatePlayerLivesDisplay(FText playerLivesCurrent);
	void UpdateLevelNameDisplay(FText levelNameDisplayText);

	void HidePumpkinCounter();
	void HideCandyCounter();
	void HideTimerDisplay();
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