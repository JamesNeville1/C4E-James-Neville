#include "W_Hud.h"

#include "C4E_Neville/Interface/GameInstanceLogic.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetTextLibrary.h"

void UW_Hud::NativeConstruct()
{
	Super::NativeConstruct();

	FText levelNameDisplayText = UKismetTextLibrary::Conv_NameToText(
		IGameInstanceLogic::Execute_GetCurrentLevel(GetGameInstance()));
	UpdateLevelNameDisplay(levelNameDisplayText);
}

void UW_Hud::UpdateHealthBar(float normalisedHealth)
{
	HealthBar->SetPercent(normalisedHealth);

	ReceiveUpdateHealthBar(normalisedHealth);
}

void UW_Hud::UpdateHealthBarColour(FLinearColor color)
{
	HealthBar->SetFillColorAndOpacity(color);

	ReceiveUpdateHealthBarColour(color);
}

void UW_Hud::UpdateCandyCounter(FString candyCurrent, FString candyMax)
{
	FString base = "";
	base.Append(candyCurrent);
	base.Append(" / ");
	base.Append(candyMax);
	CandyCounter->SetText(UKismetTextLibrary::Conv_StringToText(base));

	ReceiveUpdateCandyCounter(candyCurrent, candyMax);
}

void UW_Hud::UpdatePumpkinCounter(FString pumpkinCurrent, FString pumpkinMax)
{
	FString base = "";
	base.Append(pumpkinCurrent);
	base.Append(" / ");
	base.Append(pumpkinMax);
	PumpkinCounter->SetText(UKismetTextLibrary::Conv_StringToText(base));

	ReceiveUpdatePumpkinCounter(pumpkinCurrent, pumpkinMax);
}

void UW_Hud::UpdateTimerDisplay(FString current)
{
	TimerDisplay->SetText(UKismetTextLibrary::Conv_StringToText(current));

	ReceiveUpdateTimerDisplay(current);
}

void UW_Hud::UpdatePlayerLivesDisplay(FText playerLivesCurrent)
{
	PlayerLivesDisplay->SetText(playerLivesCurrent);

	ReceiveUpdatePlayerLivesDisplay(playerLivesCurrent);
}

void UW_Hud::UpdateLevelNameDisplay(FText levelNameDisplayText)
{
	LevelNameDisplay->SetText(levelNameDisplayText);

	ReceiveUpdateLevelNameDisplay(levelNameDisplayText);
}

void UW_Hud::HidePumpkinCounter()
{
	PumpkinCounter->SetVisibility(ESlateVisibility::Hidden);
	PumpkinCounter->RemoveFromParent();

	ReceiveHidePumpkinCounter();
}

void UW_Hud::HideCandyCounter()
{
	CandyCounter->SetVisibility(ESlateVisibility::Hidden);
	CandyCounter->RemoveFromParent();

	ReceiveHideCandyCounter();
}

void UW_Hud::HideTimerDisplay()
{
	TimerDisplay->SetVisibility(ESlateVisibility::Hidden);

	ReceiveHideTimerDisplay();
}

void UW_Hud::ReceiveUpdateHealthBar_Implementation(const float& normalisedHealth)
{
}

void UW_Hud::ReceiveUpdateHealthBarColour_Implementation(const FLinearColor& color)
{
}

void UW_Hud::ReceiveUpdateCandyCounter_Implementation(const FString& candyCurrent, const FString& candyMax)
{
}

void UW_Hud::ReceiveUpdatePumpkinCounter_Implementation(const FString& pumpkinCurrent, const FString& pumpkinMax)
{
}

void UW_Hud::ReceiveUpdateTimerDisplay_Implementation(const FString& current)
{
}

void UW_Hud::ReceiveUpdatePlayerLivesDisplay_Implementation(const FText& playerLivesCurrent)
{
}

void UW_Hud::ReceiveUpdateLevelNameDisplay_Implementation(const FText& levelNameDisplayText)
{
}

void UW_Hud::ReceiveHideTimerDisplay_Implementation()
{
}

void UW_Hud::ReceiveHidePumpkinCounter_Implementation()
{
}

void UW_Hud::ReceiveHideCandyCounter_Implementation()
{
}
