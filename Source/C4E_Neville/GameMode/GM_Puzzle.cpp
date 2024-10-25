#include "../GameMode/GM_Puzzle.h"

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

void AGM_Puzzle::BeginPlay()
{
	Super::BeginPlay();
}
