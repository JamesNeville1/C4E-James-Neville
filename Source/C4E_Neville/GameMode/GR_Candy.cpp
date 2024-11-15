﻿#include "GR_Candy.h"

#include "../Level/Candy.h"
#include "GM_Puzzle.h"
#include "C4E_Neville/Interface/CandyReturns.h"
#include "C4E_Neville/Level/Candy.h"
#include "C4E_Neville/Level/CandyComponent.h"
#include "Kismet/GameplayStatics.h"

UGR_Candy::UGR_Candy()
{
	PrimaryComponentTick.bCanEverTick = false;
	
	_IsRequiredToCompleteGame = true;
}

void UGR_Candy::BeginPlay()
{
	OnPuzzleGameRuleComplete.AddUniqueDynamic(Cast<AGM_Puzzle>(UGameplayStatics::GetGameMode(GetWorld())), &AGM_Puzzle::CandyGameRuleComplete);
	
	Super::BeginPlay();
}

void UGR_Candy::RegisterCandy(UCandyComponent* candyComponent)
{
	candyComponent->_OnCandyEaten.AddUniqueDynamic(this, &UGR_Candy::CandyEatenAlert);
	
	_CurrentCandy++;
}

void UGR_Candy::CandyEatenAlert()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("Candy Eaten"));
	_CurrentCandy -= 1;
	
	if(_CurrentCandy <= 0)
	{
		BroadcastGameRuleComplete();
	}
}
