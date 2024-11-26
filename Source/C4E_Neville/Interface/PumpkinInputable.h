// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PumpkinInputable.generated.h"

UINTERFACE()
class UPumpkinInputable : public UInterface
{
	GENERATED_BODY()
};

class C4E_NEVILLE_API IPumpkinInputable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UBehaviorTree* GetBehaviorTree();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Input_Attack(AActor* target);
};
