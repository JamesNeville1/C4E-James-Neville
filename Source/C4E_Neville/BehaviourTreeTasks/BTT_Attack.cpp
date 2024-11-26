#include "BTT_Attack.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "C4E_Neville/Interface/PumpkinInputable.h"

EBTNodeResult::Type UBTT_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	IPumpkinInputable::Execute_Input_Attack(
		OwnerComp.GetAIOwner()->GetPawn(),
		Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(Key_Target.SelectedKeyName))
	);
	
	return EBTNodeResult::Succeeded;
}
