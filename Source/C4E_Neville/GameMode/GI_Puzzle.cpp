// Fill out your copyright notice in the Description page of Project Settings.


#include "GI_Puzzle.h"

#include "Kismet/KismetStringLibrary.h"

FName UGI_Puzzle::GetNextLevel_Implementation()
{
	_CurrentLevel++;

	//GEngine->AddOnScreenDebugMessage(-1, 10000.0f, FColor::Yellow, UKismetStringLibrary::Conv_IntToString(_CurrentLevel));

	if (_CurrentLevel >= _Levels.Num())
	{
		return "";
	}

	return _Levels[_CurrentLevel].levelToLoad;
}

FName UGI_Puzzle::GetCurrentLevel_Implementation()
{
	return _Levels[_CurrentLevel].levelDisplayName;
}
