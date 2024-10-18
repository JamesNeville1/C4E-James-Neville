#include "../GameMode/GM_Puzzle.h"

#include "../Guys/P_Guy.h"
#include "../Guys/P_Guy.h"
#include "ToolBuilderUtil.h"
#include "C4E_Neville/Controller/PC_Guy.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"


AGM_Puzzle::AGM_Puzzle() { }

void AGM_Puzzle::SwapCharacter()
{
	AP_Guy* guy = FindCurrentCharacter(); //Change to Ref!

	if(guy == nullptr) { return; }

	int nextGuyInt;
	int currentGuyInt = _SwapList.Find(guy); //Map
	if(currentGuyInt == _SwapList.Num() -1)
	{
		nextGuyInt = 0;
	}
	else
	{
		nextGuyInt = currentGuyInt + 1;
	}

	_ControllerRef->Possess(_SwapList[nextGuyInt]);
}

AP_Guy* AGM_Puzzle::FindCurrentCharacter()
{
	for (AP_Guy* guy : _SwapList)
	{
		if(guy->Controller != nullptr)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, guy->Controller.GetName());
			return guy;
		}
	}
	return nullptr;
}

void AGM_Puzzle::BeginPlay()
{
	TArray<AActor*> uncastedGuys;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AP_Guy::StaticClass(), uncastedGuys);
	for (AActor* guy : uncastedGuys)
	{
		_SwapList.Add(Cast<AP_Guy>(guy));
	}

	AActor* uncastController = UGameplayStatics::GetActorOfClass(GetWorld(), APC_Guy::StaticClass());
	_ControllerRef = Cast<APC_Guy>(uncastController);
	
	Super::BeginPlay();
}
