// Fill out your copyright notice in the Description page of Project Settings.


#include "AIC_Pumpkin.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "C4E_Neville/Interface/GuyInputable.h"
#include "C4E_Neville/Interface/PumpkinInputable.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AAIC_Pumpkin::AAIC_Pumpkin()
{
	PrimaryActorTick.bCanEverTick = true;

	_AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception"));

	_AISense_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sense Sight"));
	_AISense_Sight->DetectionByAffiliation.bDetectEnemies = true;
	_AISense_Sight->DetectionByAffiliation.bDetectFriendlies = false;
	_AISense_Sight->DetectionByAffiliation.bDetectNeutrals = false;

	_AIPerception->ConfigureSense(*_AISense_Sight);
	_AIPerception->SetDominantSense(UAISenseConfig_Sight::StaticClass());

	AAIController::SetGenericTeamId(FGenericTeamId(1));
}

ETeamAttitude::Type AAIC_Pumpkin::GetTeamAttitudeTowards(const AActor& Other) const
{
	FGenericTeamId teamID(FGenericTeamId::GetTeamIdentifier(&Other));
	//GEngine->AddOnScreenDebugMessage(-1, 10000.0f, FColor::Yellow, FString::Printf(TEXT("Getting Att towards: %d"), teamID.GetId()));

	if (teamID == FGenericTeamId(1))
	{
		return ETeamAttitude::Friendly;
	}
	if (teamID == FGenericTeamId(2))
	{
		return ETeamAttitude::Hostile;
	}
	return ETeamAttitude::Neutral;
}

void AAIC_Pumpkin::BeginPlay()
{
	Super::BeginPlay();


	_AIPerception->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &AAIC_Pumpkin::Handle_TargetPerceptionUpdated);
	_AIPerception->OnTargetPerceptionForgotten.AddUniqueDynamic(this, &AAIC_Pumpkin::Handle_TargetPerceptionForgotten);
}

void AAIC_Pumpkin::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UKismetSystemLibrary::DoesImplementInterface(InPawn, UPumpkinInputable::StaticClass()))
	{
		RunBehaviorTree(IPumpkinInputable::Execute_GetBehaviorTree(InPawn));
	}
}

void AAIC_Pumpkin::Handle_TargetPerceptionUpdated(AActor* actor, FAIStimulus stimulus)
{
	//GEngine->AddOnScreenDebugMessage(-1, 10000.0f, FColor::Yellow, "Stimed");

	switch (stimulus.Type)
	{
	case 0:
		GetBlackboardComponent()->SetValueAsObject("TargetActor", actor);
		return;
	default:
		return;
	}
}

void AAIC_Pumpkin::Handle_TargetPerceptionForgotten(AActor* actor)
{
	GetBlackboardComponent()->ClearValue("TargetActor");
}
