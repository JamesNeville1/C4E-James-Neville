// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C4E_Neville/Interface/GameInstanceLogic.h"
#include "Engine/GameInstance.h"
#include "GI_Puzzle.generated.h"

USTRUCT(BlueprintType)
struct FLevelData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName levelToLoad;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName levelDisplayName;
};

UCLASS()
class C4E_NEVILLE_API UGI_Puzzle : public UGameInstance, public IGameInstanceLogic
{
	GENERATED_BODY()

public:
	virtual FName GetNextLevel_Implementation() override;
	virtual FName GetCurrentLevel_Implementation() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FLevelData> _Levels;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int _CurrentLevel;
};
