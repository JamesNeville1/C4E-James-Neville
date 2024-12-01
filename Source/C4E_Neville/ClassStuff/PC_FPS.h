// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PC_FPS.generated.h"

class AP_FPS;
class UWidget_Hud;
struct FInputActionValue;
class UInputAction;
/**
 * 
 */
UCLASS()
class C4E_NEVILLE_API APC_FPS : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, category = "Input")
	TObjectPtr<UInputAction> _LookAction;
	UPROPERTY(EditAnywhere, category = "Input")
	TObjectPtr<UInputAction> _MoveAction;
	UPROPERTY(EditAnywhere, category = "Input")
	TObjectPtr<UInputAction> _JumpAction;
	UPROPERTY(EditAnywhere, category = "Input")
	TObjectPtr<UInputAction> _FireAction;

	virtual void SetupInputComponent() override;
	void Look(const FInputActionValue& value);
	void Move(const FInputActionValue& value);
	void JumpPressed();
	void JumpReleased();
	void FirePressed();
	void FireReleased();
	virtual void OnPossess(APawn* InPawn) override;

	//Hud
	UPROPERTY(EditAnywhere)
	TSubclassOf<UWidget_Hud> _HudWidgetClass;
	TObjectPtr<UWidget_Hud> _HudWidget;

	TObjectPtr<AP_FPS> _player;

	virtual void BeginPlay() override;
};
