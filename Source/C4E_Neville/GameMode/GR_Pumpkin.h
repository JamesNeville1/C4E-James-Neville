// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleGameRule.h"
#include "GR_Pumpkin.generated.h"


class UPumpkinComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class C4E_NEVILLE_API UGR_Pumpkin : public UPuzzleGameRule
{
	GENERATED_BODY()

public:
	UGR_Pumpkin();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void RegisterPumpkin(UPumpkinComponent* pumpkinComponent);

	int _CurrentPumpkin;
	
private:
	UFUNCTION()
	void PumpkinDeathAlert();
};
