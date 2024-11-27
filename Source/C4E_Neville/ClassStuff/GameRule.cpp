#include "GameRule.h"

UGameRule::UGameRule()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UGameRule::Init()
{
}

void UGameRule::BroadcastComplete()
{
	OnComplete.Broadcast();
}

void UGameRule::BroadcastPointsScored(AController* scorer, int points)
{
	OnPointsScored.Broadcast(scorer, points);
}
