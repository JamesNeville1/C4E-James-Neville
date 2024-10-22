#include "PuzzleGameRule.h"

UPuzzleGameRule::UPuzzleGameRule()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPuzzleGameRule::BroadcastGameRuleComplete()
{
	OnPuzzleGameRuleComplete.Broadcast();
}
