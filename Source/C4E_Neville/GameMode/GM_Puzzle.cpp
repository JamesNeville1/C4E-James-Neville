#include "../GameMode/GM_Puzzle.h"

#include "GR_Candy.h"
#include "GR_Pumpkin.h"
#include "K2Node_SpawnActorFromClass.h"
#include "../Guys/P_Guy.h"
#include "../Guys/P_Guy.h"
#include "ToolBuilderUtil.h"
#include "C4E_Neville/Controller/PC_Guy.h"
#include "C4E_Neville/Guys/P_Guy_Lil.h"
#include "C4E_Neville/Guys/P_Guy_Strong.h"
#include "C4E_Neville/Level/GuyStart.h"
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
	
	TArray<AP_Guy*> guys;
	for (AActor* start : _GuyStarts)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = GetOwner();
		spawnParams.Instigator = GetInstigator();
		spawnParams.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		TSubclassOf<AP_Guy> myGuy = IGuyStaticClassReturn::Execute_Return_GuyClass(start);
		AActor* guy = GetWorld()->SpawnActor<AP_Guy>(myGuy, start->GetActorLocation(), start->GetActorRotation(), spawnParams);

		guys.Add(IGuyReturns::Execute_Return_Self(guy));
	}

	_ControllerRef->ControllerSetup(guys, sharedLivesTotal, _SwapListOrder);
	_ControllerRef->OnOutOfLives.AddUniqueDynamic(this, &AGM_Puzzle::PlayerOutOfLives);
}

void AGM_Puzzle::HandleMatchIsWaitingToStart()
{
	MyStartMatch();
}

void AGM_Puzzle::CandyGameRuleComplete()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("Candy Complete, check other GRs"));
}

void AGM_Puzzle::TimerGameRuleComplete()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Player ran out of time"));
}

void AGM_Puzzle::PumpkinGameRuleComplete()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Pumpkin Complete, check other GRs"));
}

void AGM_Puzzle::PlayerOutOfLives(AP_Guy* guyThatDied)
{
	FString output = guyThatDied->GetName() + " Died!";
				
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, output);
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