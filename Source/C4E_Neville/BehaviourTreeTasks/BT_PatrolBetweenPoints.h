#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BT_PatrolBetweenPoints.generated.h"

UCLASS()
class C4E_NEVILLE_API UBT_PatrolBetweenPoints : public UBTTaskNode
{
	GENERATED_BODY()
	

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void CheckDistance();
	
	FTimerHandle _CheckDistHandle;
};
