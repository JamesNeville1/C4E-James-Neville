// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameRuleReturns.generated.h"

class UGR_PlayerDeath;
class UGR_Pumpkin;
class UGR_Candy;
// This class does not need to be modified.
UINTERFACE()
class UGameRuleReturns : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class C4E_NEVILLE_API IGameRuleReturns
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UGR_Candy* GR_Candy_Ref();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UGR_Pumpkin* GR_Pumpkin_Ref();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UGR_PlayerDeath* GR_PlayerDeath_Ref();
};
