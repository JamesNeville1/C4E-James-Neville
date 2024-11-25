// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_GetMoveToPos.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_GetMoveToPos::UBTT_GetMoveToPos()
{
	Key_Pos.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTT_GetMoveToPos, Key_Pos));
	//Key_HasReached.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UBTT_GetMoveToPos, Key_HasReached));
}

void UBTT_GetMoveToPos::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
}

EBTNodeResult::Type UBTT_GetMoveToPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FNavLocation navLocation;
	
	UNavigationSystemV1* navigationSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	navigationSystem->GetRandomPointInNavigableRadius(
	   OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation(),
	   100000.0f,
	   navLocation
   );

	//OwnerComp.GetBlackboardComponent()->SetValueAsBool(Key_HasReached.SelectedKeyName, false);
	OwnerComp.GetBlackboardComponent()->SetValueAsVector(Key_Pos.SelectedKeyName, navLocation.Location);
	
	return EBTNodeResult::Succeeded;
}
