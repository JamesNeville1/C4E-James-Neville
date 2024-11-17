#include "GR_Candy.h"

#include "../Level/Candy.h"
#include "GM_Puzzle.h"
#include "C4E_Neville/Interface/CandyReturns.h"
#include "C4E_Neville/Interface/GuyController.h"
#include "C4E_Neville/Level/Candy.h"
#include "C4E_Neville/Level/CandyComponent.h"
#include "Kismet/GameplayStatics.h"

UGR_Candy::UGR_Candy()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	_IsRequiredToCompleteGame = true;
}

void UGR_Candy::Setup(AGM_Puzzle* gm)
{
	OnPuzzleGameRuleComplete.AddUniqueDynamic(gm, &AGM_Puzzle::CandyGameRuleComplete);
}

void UGR_Candy::RegisterCandy(UCandyComponent* candyComponent)
{
	candyComponent->_OnCandyEaten.AddUniqueDynamic(this, &UGR_Candy::CandyEatenAlert);
	
	_CurrentCandy++;
	_TotalCandy++;
}

void UGR_Candy::CandyEatenAlert()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("Candy Eaten"));
	_CurrentCandy -= 1;
	
	IGuyController::Execute_UpdateCandyAlert(UGameplayStatics::GetPlayerController(GetWorld(),0), _CurrentCandy, _TotalCandy);
	
	if(_CurrentCandy <= 0)
	{
		BroadcastGameRuleComplete();
	}
}
