﻿#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GM_Puzzle.generated.h"


class APC_Guy;
class AP_Guy;

UCLASS()
class C4E_NEVILLE_API AGM_Puzzle : public AGameMode
{
	GENERATED_BODY()

public:
	AGM_Puzzle();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AP_Guy*> _SwapList;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APC_Guy* _ControllerRef;
	
	UFUNCTION()
	void SwapCharacter();
	
	AP_Guy* FindCurrentCharacter();
	
	virtual void BeginPlay() override;
};
