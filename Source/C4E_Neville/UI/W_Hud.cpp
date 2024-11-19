#include "W_Hud.h"

#include "C4E_Neville/Interface/GameInstanceLogic.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetTextLibrary.h"

void UW_Hud::NativeConstruct()
{
	Super::NativeConstruct();

	FText levelNameDisplayText = UKismetTextLibrary::Conv_NameToText(IGameInstanceLogic::Execute_GetCurrentLevel(GetGameInstance()));
	UpdateLevelNameDisplay(levelNameDisplayText);
}

void UW_Hud::UpdateHealthBar(float normalisedHealth)
{
	HealthBar->SetPercent(normalisedHealth);
}

void UW_Hud::UpdateHealthBarColour(FLinearColor color)
{
	HealthBar->SetFillColorAndOpacity(color);
}

void UW_Hud::UpdateCandyCounter(FString candyCurrent, FString candyMax)
{
	FString base = "";
	base.Append(candyCurrent);
	base.Append(" / ");
	base.Append(candyMax);
	CandyCounter->SetText(UKismetTextLibrary::Conv_StringToText(base));
}

void UW_Hud::UpdatePumpkinCounter(FString pumpkinCurrent, FString pumpkinMax)
{
	FString base = "";
	base.Append(pumpkinCurrent);
	base.Append(" / ");
	base.Append(pumpkinMax);
	PumpkinCounter->SetText(UKismetTextLibrary::Conv_StringToText(base));
}

void UW_Hud::UpdateTimerDisplay(FString current)
{
	TimerDisplay->SetText(UKismetTextLibrary::Conv_StringToText(current));
}

void UW_Hud::UpdatePlayerLivesDisplay(FText playerLivesCurrent)
{
	PlayerLivesDisplay->SetText(playerLivesCurrent);
}

void UW_Hud::UpdateLevelNameDisplay(FText levelNameDisplayText)
{
	LevelNameDisplay->SetText(levelNameDisplayText);
}

void UW_Hud::HidePumpkinCounter()
{
	//PumpkinCounter->SetVisibility(ESlateVisibility::Hidden);
	//PumpkinCounter->RemoveFromParent();
}

void UW_Hud::HideCandyCounter()
{
	CandyCounter->SetVisibility(ESlateVisibility::Hidden);
	CandyCounter->RemoveFromParent();
}

void UW_Hud::HideTimerDisplay()
{
	TimerDisplay->SetVisibility(ESlateVisibility::Hidden);
}
