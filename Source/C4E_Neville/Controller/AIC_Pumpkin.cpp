// Fill out your copyright notice in the Description page of Project Settings.


#include "AIC_Pumpkin.h"

#include "C4E_Neville/Interface/GuyInputable.h"
#include "C4E_Neville/Interface/PumpkinInputable.h"
#include "Kismet/KismetSystemLibrary.h"

AAIC_Pumpkin::AAIC_Pumpkin()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAIC_Pumpkin::BeginPlay()
{
	Super::BeginPlay();
}

void AAIC_Pumpkin::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(UKismetSystemLibrary::DoesImplementInterface(InPawn, UPumpkinInputable::StaticClass()))
	{
		RunBehaviorTree(IPumpkinInputable::Execute_GetBehaviorTree(InPawn));
	}
}