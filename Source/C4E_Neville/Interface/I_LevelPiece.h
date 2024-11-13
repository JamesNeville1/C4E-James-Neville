// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "I_LevelPiece.generated.h"

// This class does not need to be modified.
UINTERFACE()
class ULevelPiece : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class C4E_NEVILLE_API ILevelPiece
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Trigger();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Reverse();
};
