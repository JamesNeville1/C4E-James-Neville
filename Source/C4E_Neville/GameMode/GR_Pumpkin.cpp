#include "GR_Pumpkin.h"

#include "GM_Puzzle.h"
#include "C4E_Neville/Interface/GuyController.h"
#include "C4E_Neville/Level/PumpkinComponent.h"
#include "Kismet/GameplayStatics.h"

UGR_Pumpkin::UGR_Pumpkin()
{
	PrimaryComponentTick.bCanEverTick = false;

	_IsRequiredToCompleteGame = true;
}

void UGR_Pumpkin::Setup(AGM_Puzzle* gm)
{
	OnPuzzleGameRuleComplete.AddUniqueDynamic(gm, &AGM_Puzzle::Handle_PumpkinGameRuleComplete);
}

void UGR_Pumpkin::RegisterPumpkin(UPumpkinComponent* pumpkinComponent)
{
	pumpkinComponent->_OnPumpkinDefeat.AddUniqueDynamic(this, &UGR_Pumpkin::PumpkinDeathAlert);

	_CurrentPumpkin++;
	_TotalPumpkin++;
}

void UGR_Pumpkin::PumpkinDeathAlert()
{
	_CurrentPumpkin -= 1;

	IGuyController::Execute_UpdatePumpkinAlert(UGameplayStatics::GetPlayerController(GetWorld(),0), _CurrentPumpkin, _TotalPumpkin);
	if(_CurrentPumpkin <= 0)
	{
		BroadcastGameRuleComplete();
	}
}
