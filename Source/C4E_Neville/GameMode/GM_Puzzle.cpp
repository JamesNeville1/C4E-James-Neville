#include "../GameMode/GM_Puzzle.h"

#include "GR_Candy.h"
#include "GR_Pumpkin.h"
#include "K2Node_SpawnActorFromClass.h"
#include "LevelManager.h"
#include "../Guys/P_Guy.h"
#include "../Guys/P_Guy.h"
#include "ToolBuilderUtil.h"
#include "C4E_Neville/Controller/PC_Guy.h"
#include "C4E_Neville/Guys/P_Guy_Lil.h"
#include "C4E_Neville/Guys/P_Guy_Strong.h"
#include "C4E_Neville/Interface/GameInstanceLogic.h"
#include "C4E_Neville/Level/GuyStart.h"
#include "Engine/LevelStreamingDynamic.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

AGM_Puzzle::AGM_Puzzle()
{
}

void AGM_Puzzle::PostLogin(APlayerController* NewPlayer)
{
	_ControllerRef = Cast<APC_Guy>(NewPlayer);
	
	Super::PostLogin(NewPlayer);
}

void AGM_Puzzle::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
}

AActor* AGM_Puzzle::FindPlayerStart_Implementation(AController* Player, const FString& IncomingName)
{
	if(_GuyStarts.Num() == 0)
	{
		TArray<AActor*> foundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGuyStart::StaticClass(), foundActors);
		for(AActor* actor : foundActors)
		{
			_GuyStarts.Add(actor);
		}
	}
	
	if(_GuyStarts.Num() > 0)
	{
		return _GuyStarts[FMath::RandRange(0, _GuyStarts.Num()-1)];
	}
	return nullptr;
}

void AGM_Puzzle::MyStartMatch()
{
	//TArray<AActor*> foundActors;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGuyStart::StaticClass(), foundActors);
	//_GuyStarts = foundActors;

	//Spawn Guys
	TArray<AP_Guy*> guys;
	guys.Init(nullptr, _SwapOrder.Num());
	
	for (int i = 0; i < _GuyStarts.Num(); i++)
	{
		int index = _SwapOrder.Find(IGuyStaticClassReturn::Execute_Return_GuyClass(_GuyStarts[i]));			
		
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = GetOwner();
		spawnParams.Instigator = GetInstigator();
		spawnParams.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		
		AActor* guy = GetWorld()->SpawnActor<AP_Guy>(_SwapOrder[index], _GuyStarts[i]->GetActorLocation(), _GuyStarts[i]->GetActorRotation(), spawnParams);
		guys[index] = IGuyReturns::Execute_Return_Self(guy);
	}

	//Setup Controller
	_ControllerRef->ControllerSetup(_SwapOrder, guys, sharedLivesTotal, _BigGuyCanThrow);
	_ControllerRef->OnOutOfLives.AddUniqueDynamic(this, &AGM_Puzzle::PlayerOutOfLives);

	//Setup Level Manager
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = GetOwner();
	spawnParams.Instigator = GetInstigator();
	spawnParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
	_LevelManagerRef = GetWorld()->SpawnActor<ALevelManager>(LevelManagerClass, spawnParams);
	_LevelManagerRef->LevelManagerSetup(this, guys.Num());

	//GameRuleObjectiveCounter
	TArray<UActorComponent*> gameRules = K2_GetComponentsByClass(UPuzzleGameRule::StaticClass());

	for (auto gameRule : gameRules)
	{
		if(Cast<UPuzzleGameRule>(gameRule)->_IsRequiredToCompleteGame)
		{
			_GameRuleObjectivesToComplete++;
		}
	}

	CheckGameRuleObjectivesToComplete();
}

void AGM_Puzzle::HandleMatchIsWaitingToStart()
{
	MyStartMatch();
}

void AGM_Puzzle::EnableAllEndLevels()
{
	_LevelManagerRef->EnableAllEndLevels();
}

void AGM_Puzzle::EndGame()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("GAME END"));
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
		UGameplayStatics::OpenLevel(GetWorld(), nextLevelName);
	}
}

void AGM_Puzzle::FailLevel(FString reason)
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(GetWorld()->GetName()));
}

void AGM_Puzzle::CandyGameRuleComplete()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("Candy Complete, check other GRs"));

	_GameRuleObjectivesToComplete--;
	CheckGameRuleObjectivesToComplete();
}

void AGM_Puzzle::TimerGameRuleComplete()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Player ran out of time"));

	FailLevel("Time ran out!!!");
}

void AGM_Puzzle::PumpkinGameRuleComplete()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Pumpkin Complete, check other GRs"));
	
	_GameRuleObjectivesToComplete--;
	CheckGameRuleObjectivesToComplete();
}

void AGM_Puzzle::PlayerOutOfLives(AP_Guy* guyThatDied)
{
	FString output = guyThatDied->GetName() + " Died!";
				
	FailLevel(output);
}


void AGM_Puzzle::BeginPlay()
{
	_CandyGRRef = Cast<UGR_Candy>(GetComponentByClass(UGR_Candy::StaticClass()));
	_PumpkinGRRef = Cast<UGR_Pumpkin>(GetComponentByClass(UGR_Pumpkin::StaticClass()));
	
	Super::BeginPlay();
}

UGR_Candy* AGM_Puzzle::GR_Candy_Ref_Implementation()
{
	return _CandyGRRef;
}

UGR_Pumpkin* AGM_Puzzle::GR_Pumpkin_Ref_Implementation()
{
	return _PumpkinGRRef;
}

void AGM_Puzzle::CheckGameRuleObjectivesToComplete()
{
	if(_GameRuleObjectivesToComplete == 0)
	{
		_LevelManagerRef->EnableAllEndLevels();
	}
}
