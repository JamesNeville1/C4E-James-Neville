#include "BT_PatrolBetweenPoints.h"

#include "C4E_Neville/Controller/AIC_Pumpkin.h"
#include "C4E_Neville/Interface/GuyInputable.h"
#include "C4E_Neville/Interface/PumpkinInputable.h"
#include "Kismet/KismetStringLibrary.h"
#include "Tasks/AITask_MoveTo.h"

EBTNodeResult::Type UBT_PatrolBetweenPoints::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(OwnerComp.GetAIOwner()->GetMoveStatus() != EPathFollowingStatus::Moving)
	{
		EPathFollowingRequestResult::Type res = OwnerComp.GetAIOwner()->MoveToLocation(
			IPumpkinInputable::Execute_GetNextPatrolPoint(OwnerComp.GetAIOwner()->GetPawn()));
	}

	//GetWorld()->GetTimerManager().SetTimer(_CheckDistHandle, this, &UGR_Timer::BroadcastGameRuleComplete, _length, false);
	
	return EBTNodeResult::InProgress;
}

void UBT_PatrolBetweenPoints::CheckDistance()
{
}
