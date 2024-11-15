// Fill out your copyright notice in the Description page of Project Settings.


#include "GI_Puzzle.h"

FName UGI_Puzzle::GetNextLeve()
{
	_CurrentLevel++;

	if(_LevelMap.Find(_CurrentLevel) == new FName(""))
	{
		return "";
	}

	return  _LevelMap[_CurrentLevel];
}
