// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GuyInputable.generated.h"

class UInputMappingContext;

// This class does not need to be modified.
UINTERFACE()
class UGuyInputable : public UInterface
{
	GENERATED_BODY()
};

class C4E_NEVILLE_API IGuyInputable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintInternalUseOnly)
	void Input_Look(FVector2D value);
	UFUNCTION(BlueprintNativeEvent, BlueprintInternalUseOnly)
	void Input_MovePressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintInternalUseOnly)
	void Input_MoveReleased();
	UFUNCTION(BlueprintNativeEvent, BlueprintInternalUseOnly)
	void Input_Move(FVector2D value);
	UFUNCTION(BlueprintNativeEvent, BlueprintInternalUseOnly)
	void Input_JumpPressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintInternalUseOnly)
	void Input_JumpReleased();
	UFUNCTION(BlueprintNativeEvent, BlueprintInternalUseOnly)
	void Input_SpecialPressed();
	UFUNCTION(BlueprintNativeEvent, BlueprintInternalUseOnly)
	void Input_CharacterSwapPressed();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintInternalUseOnly)
	UInputMappingContext* GetMappingContext();
};
