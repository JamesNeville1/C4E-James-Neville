// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InfoReturns.generated.h"

class UGR_Candy;
class UGI_Info;
// This class does not need to be modified.
UINTERFACE()
class UInfoReturns : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class C4E_NEVILLE_API IInfoReturns
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UGI_Info* ReturnInstance();
};
