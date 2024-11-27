// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTS_GetDistanceFromActor.generated.h"

/**
 * 
 */
UCLASS()
class C4E_NEVILLE_API UBTS_GetDistanceFromActor : public UBTService
{
	GENERATED_BODY()

public:
	UBTS_GetDistanceFromActor();

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category="Blackboard")
	FBlackboardKeySelector Key_Target;
	UPROPERTY(EditAnywhere, Category="Blackboard")
	FBlackboardKeySelector Key_Self;
	UPROPERTY(EditAnywhere, Category="Blackboard")
	FBlackboardKeySelector Key_DistanceOutput;
};
