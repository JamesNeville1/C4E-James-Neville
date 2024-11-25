// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_GetMoveToPos.generated.h"

UCLASS()
class C4E_NEVILLE_API UBTT_GetMoveToPos : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTT_GetMoveToPos();
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere, Category="Blackboard")
	FBlackboardKeySelector Key_HasReached;
	UPROPERTY(EditAnywhere, Category="Blackboard")
	FBlackboardKeySelector Key_Pos;
	UPROPERTY(EditAnywhere, Category="Node")
	float _RandomRadius;
};
