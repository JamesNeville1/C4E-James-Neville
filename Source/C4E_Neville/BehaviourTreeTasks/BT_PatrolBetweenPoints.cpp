#include "BT_PatrolBetweenPoints.h"

#include "C4E_Neville/Controller/AIC_Pumpkin.h"
#include "C4E_Neville/Interface/GuyInputable.h"
#include "C4E_Neville/Interface/PumpkinInputable.h"
#include "C4E_Neville/Level/Pumpkin.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Tasks/AITask_MoveTo.h"

EBTNodeResult::Type UBT_PatrolBetweenPoints::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetAIOwner()->MoveToLocation(
		IPumpkinInputable::Execute_GetNextPatrolPoint(OwnerComp.GetAIOwner()->GetPawn()));

	// GetWorld()->GetTimerManager().SetTimer(
	// 	_CheckDistHandle,
	// 	Cast<APumpkin>(OwnerComp.GetAIOwner()->GetPawn()), &APumpkin::CheckIfAtPatrolPoint_Implementation,
	// 	3.0f, false);
	
	return EBTNodeResult::InProgress;
}

void UBT_PatrolBetweenPoints::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	bool closeEnough = UKismetMathLibrary::Vector_Distance(
		OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation(),
		IPumpkinInputable::Execute_GetCurrentPatrolPoint(OwnerComp.GetAIOwner()->GetPawn())) < 100;

	if(closeEnough)
	{
		//OwnerComp.GetBlackboardComponent().set
	}
}
