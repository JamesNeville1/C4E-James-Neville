// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelManager.generated.h"

class ALevelEnd;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndLevelCounterAlertSignature);

UCLASS()
class C4E_NEVILLE_API ALevelManager : public AActor
{
	GENERATED_BODY()

public:
	ALevelManager();
	UFUNCTION()
	void LevelManagerSetup(AGM_Puzzle* gamemode, int endLevelCounterMax);

	UFUNCTION()
	void EndLevelCounterIncrease();
	UFUNCTION()
	void EndLevelCounterDecrease();

	UFUNCTION()
	void EnableAllEndLevels();
	
private:
	int _EndLevelCounter;
	int _EndLevelCounterMax;

	TArray<ALevelEnd*> _LevelEnds;
	
	FEndLevelCounterAlertSignature OnEndLevelCounterAlert;
};
