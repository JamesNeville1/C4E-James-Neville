// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PC_Debug.generated.h"

struct FInputActionValue;
class UInputAction;
/**
 * 
 */
UCLASS(Abstract)
class C4E_NEVILLE_API APC_Debug : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> _DebugAction;
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> _JumpAction;
	virtual void SetupInputComponent() override;

	void Debug(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);
	void MoveX(const FInputActionValue& Value);
	void MoveY(const FInputActionValue& Value);
	void Sprint(const FInputActionValue& Value);
	void Special(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	
};
