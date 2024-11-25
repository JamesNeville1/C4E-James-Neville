#include "BTT_Attack.h"

EBTNodeResult::Type UBTT_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	GEngine->AddOnScreenDebugMessage(-1, 10000.0f, FColor::Yellow, "Test A");
	
	return EBTNodeResult::Succeeded;
}
