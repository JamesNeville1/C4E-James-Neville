#include "BT_PatrolBetweenPoints.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "C4E_Neville/Controller/AIC_Pumpkin.h"
#include "NavigationSystem.h"



EBTNodeResult::Type UBT_PatrolBetweenPoints::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//GEngine->AddOnScreenDebugMessage(-1, 10000.0f, FColor::Yellow, "BEANS");

	FNavLocation navLocation;
	
	UNavigationSystemV1* navigationSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	 navigationSystem->GetRandomPointInNavigableRadius(
		OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation(),
		100000.0f,
		navLocation
	);

	OwnerComp.GetAIOwner()->MoveToLocation(navLocation.Location);

	OwnerComp.GetBlackboardComponent()->SetValueAsBool("ReachedPatrolPoint", false);
	OwnerComp.GetBlackboardComponent()->SetValueAsVector("TargetPos", navLocation.Location);
	
	return EBTNodeResult::Succeeded;
}