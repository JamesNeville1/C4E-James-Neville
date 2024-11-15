// Fill out your copyright notice in the Description page of Project Settings.


#include "GI_Puzzle.h"

FName UGI_Puzzle::GetNextLevel_Implementation()
{
	_CurrentLevel++;

	if(_CurrentLevel >= _Levels.Num() -1)
	{
		return "";
	}

	return  _Levels[_CurrentLevel];
}
