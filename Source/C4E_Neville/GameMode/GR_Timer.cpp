#include "GR_Timer.h"

#include "GM_Puzzle.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

UGR_Timer::UGR_Timer()
{

}


void UGR_Timer::BeginPlay()
{
	OnPuzzleGameRuleComplete.AddUniqueDynamic(Cast<AGM_Puzzle>(UGameplayStatics::GetGameMode(GetWorld())), &AGM_Puzzle::TimerGameRuleComplete);

	GetWorld()->GetTimerManager().SetTimer(_StopWatchHandle, this, &UGR_Timer::BroadcastGameRuleComplete, _length, false);
	
	Super::BeginPlay();
}

