#include "W_Hud.h"

#include "C4E_Neville/Interface/GameInstanceLogic.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetTextLibrary.h"

void UW_Hud::NativeConstruct()
{
	Super::NativeConstruct();

	FText levelNameDisplayText = UKismetTextLibrary::Conv_NameToText(IGameInstanceLogic::Execute_GetCurrentLevel(GetGameInstance()));
	UpdateLevelNameDisplay(levelNameDisplayText);
}

void UW_Hud::Setup(FString playerStartingLives, FString pumpkinTotal, FString candyTotal)
{
	UpdatePlayerLivesDisplay(playerStartingLives, playerStartingLives);
	UpdateCandyCounter(candyTotal, candyTotal);
	UpdatePumpkinCounter(pumpkinTotal, pumpkinTotal);
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
}

void UW_Hud::UpdatePlayerLivesDisplay(FString playerLivesCurrent, FString playerLivesMax)
{
	FString base = "";
	base.Append(playerLivesCurrent);
	base.Append(" / ");
	base.Append(playerLivesMax);
	PlayerLivesDisplay->SetText(UKismetTextLibrary::Conv_StringToText(base));
}

void UW_Hud::UpdateLevelNameDisplay(FText levelNameDisplayText)
{
		LevelNameDisplay->SetText(levelNameDisplayText);
}
