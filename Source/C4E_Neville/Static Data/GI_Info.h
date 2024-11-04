// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Interface/InfoReturns.h"

#include "GI_Info.generated.h"

UCLASS()
class C4E_NEVILLE_API UGI_Info : public UGameInstance, public IInfoReturns
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UGR_Candy* _CandyGR;

	virtual UGI_Info* ReturnInstance_Implementation() override;
};
