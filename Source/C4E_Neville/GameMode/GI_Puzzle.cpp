// Fill out your copyright notice in the Description page of Project Settings.


#include "GI_Puzzle.h"

FName UGI_Puzzle::GetNextLevel_Implementation()
{
	_CurrentLevel++;

	if(_CurrentLevel >= _Levels.Num())
	{
		return "";
	}

	return  _Levels[_CurrentLevel];
}
