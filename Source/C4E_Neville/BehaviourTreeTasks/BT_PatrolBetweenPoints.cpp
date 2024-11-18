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
		OwnerComp.GetAIOwner()->MoveToLocation(IPumpkinInputable::Execute_GetNextPatrolPoint(OwnerComp.GetAIOwner()->GetPawn()));	
	}
	
	return EBTNodeResult::Succeeded;
}
