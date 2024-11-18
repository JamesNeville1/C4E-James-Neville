#include "BT_PatrolBetweenPoints.h"

#include "C4E_Neville/Controller/AIC_Pumpkin.h"
#include "C4E_Neville/Interface/GuyInputable.h"
#include "Kismet/KismetStringLibrary.h"
#include "Tasks/AITask_MoveTo.h"

EBTNodeResult::Type UBT_PatrolBetweenPoints::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//IGuyInputable::Execute_Input_Move(OwnerComp.GetAIOwner()->GetPawn(), FVector2d());

	OwnerComp.GetAIOwner()->MoveToLocation(FVector(0,0,0));
	
	return EBTNodeResult::Succeeded;
}
