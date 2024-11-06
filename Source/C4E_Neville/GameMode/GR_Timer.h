// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleGameRule.h"
#include "GR_Timer.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class C4E_NEVILLE_API UGR_Timer : public UPuzzleGameRule
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGR_Timer();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float _length; 
private:
	FTimerHandle _StopWatchHandle;

	
};
