#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_CheckIfCloseEnough.generated.h"

UCLASS()
class C4E_NEVILLE_API UBTT_CheckIfCloseEnough : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTT_CheckIfCloseEnough();

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category="Blackboard")
	FBlackboardKeySelector Key_HasReachedOutput;
	UPROPERTY(EditAnywhere, Category="Blackboard")
	FBlackboardKeySelector Key_Distance;
	UPROPERTY(EditAnywhere, Category="Blackboard")
	FBlackboardKeySelector Key_DistanceAllowance;
	
};
