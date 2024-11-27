// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PuzzleGameRuleCheck.generated.h"

class AGM_Puzzle;

UINTERFACE()
class UPuzzleGameRuleLogic : public UInterface
{
	GENERATED_BODY()
};

class C4E_NEVILLE_API IPuzzleGameRuleLogic
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool IsObjectiveGameRule();
};
