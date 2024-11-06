// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C4E_Neville/Guys/P_Guy_Big.h"
#include "UObject/Interface.h"
#include "LilGuyPickupAlert.generated.h"

// This class does not need to be modified.
UINTERFACE()
class ULilGuyPickupAlert : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class C4E_NEVILLE_API ILilGuyPickupAlert
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PickupAlert(AP_Guy_Big* bigGuyRef);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ThrowAlert(AP_Guy_Big* bigGuyRef, float throwSpeed);
};
