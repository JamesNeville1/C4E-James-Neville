#include "../GameMode/GM_Puzzle.h"

#include "GR_Candy.h"
#include "GR_Pumpkin.h"
#include "GR_Timer.h"
#include "LevelManager.h"
#include "../Guys/P_Guy.h"
#include "C4E_Neville/Controller/PC_Guy.h"
#include "C4E_Neville/Interface/GameInstanceLogic.h"
#include "C4E_Neville/Level/GuyStart.h"
#include "Kismet/GameplayStatics.h"

AGM_Puzzle::AGM_Puzzle() { }

#pragma region Controller Login/Logout

void AGM_Puzzle::PostLogin(APlayerController* NewPlayer)
{
	_ControllerRef = Cast<APC_Guy>(NewPlayer);
	
	Super::PostLogin(NewPlayer);
}

void AGM_Puzzle::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
}

#pragma endregion

#pragma region Exec Order

void AGM_Puzzle::HandleMatchIsWaitingToStart()
{
	//Get Spawns
	if(_GuyStarts.Num() == 0)
	{
		TArray<AActor*> foundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGuyStart::StaticClass(), foundActors);
		for(AActor* actor : foundActors)
		{
			_GuyStarts.Add(actor);
		}
	}
	
	//Spawn Guys
	TArray<AP_Guy*> guys;
	
	for (int i = 0; i < _GuyStarts.Num(); i++)
	{
		TSubclassOf<AP_Guy> type = IGuyStaticClassReturn::Execute_Return_GuyClass(_GuyStarts[i]);			
		
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = GetOwner();
		spawnParams.Instigator = GetInstigator();
		spawnParams.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		AActor* guy = GetWorld()->SpawnActor<AP_Guy>(type, _GuyStarts[i]->GetActorLocation(), _GuyStarts[i]->GetActorRotation(), spawnParams);
		guys.Add(Cast<AP_Guy>(guy));
	}

	RecieveGuysSpawned(guys);

	//GRs with setups, can be done with begin play, but allows me to controller the execution order
	_CandyGRRef = Cast<UGR_Candy>(GetComponentByClass(UGR_Candy::StaticClass()));
	if(_CandyGRRef != nullptr)
	{
		_CandyGRRef->Setup(this);
	}
	
	_PumpkinGRRef = Cast<UGR_Pumpkin>(GetComponentByClass(UGR_Pumpkin::StaticClass()));
	if(_PumpkinGRRef != nullptr)
	{
		_PumpkinGRRef->Setup(this);
	}
	
	_HasTimer = GetComponentByClass(UGR_Timer::StaticClass()) != nullptr;

	RecieveGameRuleSetup();
	
	//Setup Controller
	_ControllerRef->ControllerSetup(guys, _SharedLivesTotal);
	_ControllerRef->OnOutOfLives.AddUniqueDynamic(this, &AGM_Puzzle::PlayerOutOfLives);

	RecieveControllerSetup();
	
	//Setup Level Manager
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = GetOwner();
	spawnParams.Instigator = GetInstigator();
	spawnParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
	_LevelManagerRef = GetWorld()->SpawnActor<ALevelManager>(_LevelManagerClass, spawnParams);
	_LevelManagerRef->LevelManagerSetup(this, guys.Num());

	RecieveLevelManagerSetup();
	
	//GameRuleObjectiveCounter
	TArray<UActorComponent*> gameRules = K2_GetComponentsByClass(UPuzzleGameRule::StaticClass());
	
	for (auto gameRule : gameRules)
	{
		if(IPuzzleGameRuleLogic::Execute_IsObjectiveGameRule(gameRule))
		{
			_GameRuleObjectivesToComplete++;
		}
	}
	
	CheckGameRuleObjectivesToComplete();
	
	//Late Begin Player (Used to trigger things after all begin plays)
	GetWorld()->GetOnBeginPlayEvent().AddUObject(this, &AGM_Puzzle::DelayedBeginPlay);
}

void AGM_Puzzle::DelayedBeginPlay(bool played)
{
	//GEngine->AddOnScreenDebugMessage(-1, 10000.0f, FColor::Yellow, TEXT("C"));
	
	int totalCandy = 0;
	int totalPumpkin = 0;
	
	if (_CandyGRRef != nullptr)
	{
		totalCandy = _CandyGRRef->_CurrentCandy;
	}
	
	if (_PumpkinGRRef != nullptr)
	{
		totalPumpkin = _PumpkinGRRef->_CurrentPumpkin;
	}
	
	_ControllerRef->UISetupAlert(totalCandy, totalPumpkin, _HasTimer);
}

#pragma endregion

#pragma region Level Control

void AGM_Puzzle::EnableAllEndLevels()
{
	_LevelManagerRef->EnableAllEndLevels();
}

void AGM_Puzzle::EndGame()
{
	RecieveEndGame();
}

void AGM_Puzzle::EndLevel()
{
	FName nextLevelName = IGameInstanceLogic::Execute_GetNextLevel(GetGameInstance());

	if(nextLevelName == TEXT(""))
	{
		EndGame();
	}
	else
	{
		RecieveEndLevel();
		
		UGameplayStatics::OpenLevel(GetWorld(), nextLevelName);
	}
}

void AGM_Puzzle::FailLevel()
{
	RecieveFailLevel();
	
	UGameplayStatics::OpenLevel(GetWorld(), FName(GetWorld()->GetName()));
}

void AGM_Puzzle::Handle_CandyGameRuleComplete()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("Candy Complete, check other GRs"));

	RecieveCandyGameRuleComplete();
	
	_GameRuleObjectivesToComplete--;
	CheckGameRuleObjectivesToComplete();
}

void AGM_Puzzle::Handle_TimerGameRuleComplete()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Player ran out of time"));

	RecieveTimerGameRuleComplete();
	
	FailLevel();
}

void AGM_Puzzle::Handle_PumpkinGameRuleComplete()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Pumpkin Complete, check other GRs"));

	RecievePumpkinGameRuleComplete();
	
	_GameRuleObjectivesToComplete--;
	CheckGameRuleObjectivesToComplete();
}

void AGM_Puzzle::PlayerOutOfLives(AP_Guy* guyThatDied)
{
	FString output = guyThatDied->GetName() + " Died!";

	RecievePlayerOutOfLives(guyThatDied);
	
	FailLevel();
}

void AGM_Puzzle::CheckGameRuleObjectivesToComplete()
{
	if(_GameRuleObjectivesToComplete == 0)
	{
		_LevelManagerRef->EnableAllEndLevels();
	}
}

#pragma endregion

#pragma region Return Gamerules

UGR_Candy* AGM_Puzzle::GR_Candy_Ref_Implementation()
{
	return _CandyGRRef;
}

UGR_Pumpkin* AGM_Puzzle::GR_Pumpkin_Ref_Implementation()
{
	return _PumpkinGRRef;
}


#pragma endregion

#pragma region Hooks

void AGM_Puzzle::RecieveGuysSpawned_Implementation(const TArray<AP_Guy*>& guys)
{
}

void AGM_Puzzle::RecieveGameRuleSetup_Implementation()
{
}

void AGM_Puzzle::RecieveControllerSetup_Implementation()
{
}

void AGM_Puzzle::RecieveLevelManagerSetup_Implementation()
{
}

void AGM_Puzzle::RecieveDelayedBeginPlay_Implementation()
{
}

void AGM_Puzzle::RecieveFailLevel_Implementation()
{
}

void AGM_Puzzle::RecieveEndLevel_Implementation()
{
}

void AGM_Puzzle::RecieveEndGame_Implementation()
{
}

void AGM_Puzzle::RecieveCandyGameRuleComplete_Implementation()
{
}

void AGM_Puzzle::RecievePumpkinGameRuleComplete_Implementation()
{
}

void AGM_Puzzle::RecieveTimerGameRuleComplete_Implementation()
{
}

void AGM_Puzzle::RecievePlayerOutOfLives_Implementation(const AP_Guy* guyThatDied)
{
}

#pragma endregion
