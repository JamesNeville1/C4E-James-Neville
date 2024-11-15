// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GI_Puzzle.generated.h"

UCLASS()
class C4E_NEVILLE_API UGI_Puzzle : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION()
	FName GetNextLeve();
protected:
	TMap<int, FName> _LevelMap;

	int _CurrentLevel;
};
