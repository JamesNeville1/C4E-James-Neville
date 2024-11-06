#include "GR_PlayerDeath.h"

#include "GM_Puzzle.h"
#include "Kismet/GameplayStatics.h"

UGR_PlayerDeath::UGR_PlayerDeath()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UGR_PlayerDeath::BeginPlay()
{
	Super::BeginPlay();
	
	OnPuzzleGameRuleComplete.AddUniqueDynamic(Cast<AGM_Puzzle>(UGameplayStatics::GetGameMode(GetWorld())), &AGM_Puzzle::PlayerDeathGameRuleComplete);
}

void UGR_PlayerDeath::AlertPlayerDeath()
{
	if(_SharedLives == 0)
	{
		BroadcastGameRuleComplete();
		return;
	}

	_SharedLives--;
	
}

