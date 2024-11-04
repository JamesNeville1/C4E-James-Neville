// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleGameRule.h"
#include "GR_Candy.generated.h"


class UCandyComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class C4E_NEVILLE_API UGR_Candy : public UPuzzleGameRule
{
	GENERATED_BODY()

public:
	UGR_Candy();
	virtual void BeginPlay() override;
	
	int _CurrentCandy;
	UFUNCTION()
	void RegisterCandies();
	UFUNCTION()
	void CandyEatenAlert();
};
