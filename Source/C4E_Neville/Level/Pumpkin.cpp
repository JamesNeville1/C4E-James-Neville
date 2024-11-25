#include "Pumpkin.h"

#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

APumpkin::APumpkin()
{
	PrimaryActorTick.bCanEverTick = true;	
}

void APumpkin::AISetup()
{
	
}

void APumpkin::BeginPlay()
{
	Super::BeginPlay();
}

UBehaviorTree* APumpkin::GetBehaviorTree_Implementation()
{
	return _BehaviorTree;
}

FVector APumpkin::GetNextPatrolPoint_Implementation()
{
	if(_PatrolPointIndex >= _PatrolPoints.Num())
	{
		_PatrolPointIndex = 0;
	}
	
	FVector pos = _PatrolPoints[_PatrolPointIndex]->GetActorLocation(); 
	_PatrolPointIndex++;
	
	return pos;
}

FVector APumpkin::GetCurrentPatrolPoint_Implementation()
{
	return _PatrolPoints[_PatrolPointIndex]->GetActorLocation();
}

