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
	
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Update Health Bar")
	void ReceiveUpdateHealthBar(const float& normalisedHealth);
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Update Health Bar Colour")
	void ReceiveUpdateHealthBarColour(const FLinearColor& color);
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Update Candy Counter")
	void ReceiveUpdateCandyCounter(const FString& candyCurrent, const FString& candyMax);
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Update Pumpkin Counter")
	void ReceiveUpdatePumpkinCounter(const FString& pumpkinCurrent, const FString& pumpkinMax);
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Update Timer Display")
	void ReceiveUpdateTimerDisplay(const FString& current);
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Update Player Lives Display")
	void ReceiveUpdatePlayerLivesDisplay(const FText& playerLivesCurrent);
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Update Level Name Display")
	void ReceiveUpdateLevelNameDisplay(const FText& levelNameDisplayText);

	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Hide Pumpkin Counter")
	void ReceiveHidePumpkinCounter();
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Hide Candy Counter")
	void ReceiveHideCandyCounter();
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Hide Timer Display")
	void ReceiveHideTimerDisplay();

	
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
