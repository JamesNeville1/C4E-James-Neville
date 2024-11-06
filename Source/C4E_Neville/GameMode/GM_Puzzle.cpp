#include "../GameMode/GM_Puzzle.h"

#include "GR_Candy.h"
#include "../Guys/P_Guy.h"
#include "../Guys/P_Guy.h"
#include "ToolBuilderUtil.h"
#include "C4E_Neville/Controller/PC_Guy.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

AGM_Puzzle::AGM_Puzzle()
{
}

void AGM_Puzzle::PostLogin(APlayerController* NewPlayer)
{
	_ControllerRef = Cast<APC_Guy>(NewPlayer);

	_ControllerRef->SwapCharacterSetup();
	
	Super::PostLogin(NewPlayer);
}

void AGM_Puzzle::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
}

void AGM_Puzzle::CandyGameRuleComplete()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("Candy Complete, check other GRs"));
}

void AGM_Puzzle::TimerGameRuleComplete()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Player ran out of time"));
}


void AGM_Puzzle::BeginPlay()
{
	_CandyGRRef = Cast<UGR_Candy>(GetComponentByClass(UGR_Candy::StaticClass()));
	
	Super::BeginPlay();
}

UGR_Candy* AGM_Puzzle::GR_Candy_Ref_Implementation()
{
	return _CandyGRRef;
}
