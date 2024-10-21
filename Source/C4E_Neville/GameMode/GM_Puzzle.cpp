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


void AGM_Puzzle::SwapCharacter()
{
	AP_Guy* player = IGuyReturns::Execute_Return_Self(_ControllerRef->GetCharacter());
	_ControllerRef->Possess(_SwapList[player]);
}

void AGM_Puzzle::BeginPlay()
{
	//Swap Setup
	TArray<TSubclassOf<AP_Guy>> swapListOrderKeys;
	_SwapListOrder.GenerateKeyArray(swapListOrderKeys);

	//Setup Swap Order
	for (TSubclassOf<AP_Guy> guyClass : swapListOrderKeys)
	{
		//Get object reference from class reference map
		AP_Guy* key;
		AP_Guy* value;
		key = IGuyReturns::Execute_Return_Self(UGameplayStatics::GetActorOfClass(GetWorld(), guyClass));
		value = IGuyReturns::Execute_Return_Self(UGameplayStatics::GetActorOfClass(GetWorld(), _SwapListOrder[guyClass]));

		//Add to map
		_SwapList.Add(
			key,
			value
		);
	}

	//Controller Ref
	AActor* uncastController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	_ControllerRef = Cast<APC_Guy>(uncastController);
	
	//Other
	Super::BeginPlay();
}
