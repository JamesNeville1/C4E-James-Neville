// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "AIC_Pumpkin.generated.h"

UCLASS()
class C4E_NEVILLE_API AAIC_Pumpkin : public AAIController
{
	GENERATED_BODY()

public:
	AAIC_Pumpkin();

protected:
	virtual void BeginPlay() override;
	
	virtual void OnPossess(APawn* InPawn) override;	
};
