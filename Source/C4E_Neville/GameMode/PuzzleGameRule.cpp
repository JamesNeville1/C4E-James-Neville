#include "PuzzleGameRule.h"

UPuzzleGameRule::UPuzzleGameRule()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UPuzzleGameRule::IsObjectiveGameRule_Implementation()
{
	return _IsRequiredToCompleteGame;
}

void UPuzzleGameRule::BroadcastGameRuleComplete()
{
	OnPuzzleGameRuleComplete.Broadcast();
}
