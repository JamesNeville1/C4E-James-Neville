#include "GR_Pumpkin.h"

#include "GM_Puzzle.h"
#include "C4E_Neville/Level/PumpkinComponent.h"
#include "Kismet/GameplayStatics.h"

UGR_Pumpkin::UGR_Pumpkin()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGR_Pumpkin::BeginPlay()
{
	OnPuzzleGameRuleComplete.AddUniqueDynamic(Cast<AGM_Puzzle>(UGameplayStatics::GetGameMode(GetWorld())), &AGM_Puzzle::PumpkinGameRuleComplete);
	
	Super::BeginPlay();
}

void UGR_Pumpkin::RegisterPumpkin(UPumpkinComponent* pumpkinComponent)
{
	pumpkinComponent->_OnPumpkinDefeat.AddUniqueDynamic(this, &UGR_Pumpkin::PumpkinDeathAlert);

	_CurrentPumpkin++;
}

void UGR_Pumpkin::PumpkinDeathAlert()
{
	_CurrentPumpkin -= 1;

	if(_CurrentPumpkin <= 0)
	{
		BroadcastGameRuleComplete();
	}
}
