#include "BTT_CheckIfCloseEnough.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTT_CheckIfCloseEnough::UBTT_CheckIfCloseEnough()
{
	Key_HasReachedOutput.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UBTT_CheckIfCloseEnough, Key_HasReachedOutput));
	Key_Distance.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UBTT_CheckIfCloseEnough, Key_Distance));
}

void UBTT_CheckIfCloseEnough::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
}

EBTNodeResult::Type UBTT_CheckIfCloseEnough::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* bbComp = OwnerComp.GetBlackboardComponent();
	if(bbComp->GetValueAsFloat(Key_Distance.SelectedKeyName) <= bbComp->GetValueAsFloat(Key_DistanceAllowance.SelectedKeyName))
	{
		bbComp->SetValueAsBool(Key_HasReachedOutput.SelectedKeyName, true);
	}
	else
	{
		bbComp->SetValueAsBool(Key_HasReachedOutput.SelectedKeyName, false);
	}

	return EBTNodeResult::Succeeded;
}