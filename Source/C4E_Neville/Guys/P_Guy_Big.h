// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "P_Guy.h"
#include "P_Guy_Big.generated.h"

class AP_Guy_Lil;

UCLASS(Abstract)
class C4E_NEVILLE_API AP_Guy_Big : public AP_Guy
{
	GENERATED_BODY()

public:
	AP_Guy_Big();
	virtual void Input_CharacterSwapPressed_Implementation() override;
	virtual void Input_JumpPressed_Implementation() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UChildActorComponent> _LilGuyAttachPoint;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float _SpecialRange;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	bool holdingLilGuy;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float launchSpeed;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	AActor* _LilGuyRef; //ToDo: Ref ok?

	void SetCanThrow(bool canThrow);
	
private:
	UFUNCTION()
	void ThrowLogic();
};
