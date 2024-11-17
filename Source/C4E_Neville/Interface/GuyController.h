// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GuyController.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UGuyController : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class C4E_NEVILLE_API IGuyController
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateTimerAlert(float time);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateCandyAlert(int current, int max);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdatePumpkinAlert(int current, int max);
};
