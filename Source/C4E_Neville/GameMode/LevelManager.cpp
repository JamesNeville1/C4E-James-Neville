#include "LevelManager.h"

#include "GM_Puzzle.h"
#include "C4E_Neville/Level/LevelEnd.h"
#include "Kismet/GameplayStatics.h"

ALevelManager::ALevelManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ALevelManager::LevelManagerSetup(AGM_Puzzle* gamemode, int endLevelCounterMax)
{
	TArray<AActor*> foundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALevelEnd::StaticClass(), foundActors);

	for (auto foundActor : foundActors)
	{
		ALevelEnd* levelEnd = Cast<ALevelEnd>(foundActor);
		levelEnd->Register(this);
		_LevelEnds.Add(levelEnd);
	}

	_EndLevelCounterMax = endLevelCounterMax;

	OnEndLevelCounterAlert.AddUniqueDynamic(gamemode, &AGM_Puzzle::EndLevel);
}

void ALevelManager::EndLevelCounterIncrease()
{
	_EndLevelCounter++;

	if(_EndLevelCounter >= _EndLevelCounterMax)
	{
		OnEndLevelCounterAlert.Broadcast();
	}
}

void ALevelManager::EndLevelCounterDecrease()
{
	_EndLevelCounter--;
}

void ALevelManager::EnableAllEndLevels()
{
	for (auto levelEnd : _LevelEnds)
	{
		levelEnd->Enable();
	}
}
