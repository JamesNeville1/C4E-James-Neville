#include "GR_Timer.h"

#include "GM_Puzzle.h"
#include "C4E_Neville/Interface/GuyController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

UGR_Timer::UGR_Timer()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGR_Timer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	IGuyController::Execute_UpdateTimerAlert(
		UGameplayStatics::GetPlayerController(GetWorld(), 0),
		UKismetSystemLibrary::K2_GetTimerRemainingTimeHandle(GetWorld(),
		_StopWatchHandle));
	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UGR_Timer::BeginPlay()
{
	OnPuzzleGameRuleComplete.AddUniqueDynamic(Cast<AGM_Puzzle>(UGameplayStatics::GetGameMode(GetWorld())), &AGM_Puzzle::TimerGameRuleComplete);

	GetWorld()->GetTimerManager().SetTimer(_StopWatchHandle, this, &UGR_Timer::BroadcastGameRuleComplete, _length, false);
	
	Super::BeginPlay();
}



