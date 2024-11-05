// Fill out your copyright notice in the Description page of Project Settings.


#include "GR_Timer.h"

#include "GM_Puzzle.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
UGR_Timer::UGR_Timer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UGR_Timer::BeginPlay()
{
	//AGameMode gamemode = UGameplayStatics::GetGameMode(GetWorld());
	//OnPuzzleGameRuleComplete.AddUniqueDynamic(gamemode, &AGM_Puzzle::TimerGameRuleComplete);
	
	Super::BeginPlay();
}

