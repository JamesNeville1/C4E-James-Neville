// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C4E_Neville/Interface/GuyStartReturns.h"
#include "GameFramework/Actor.h"
#include "GuyStart.generated.h"

UCLASS()
class C4E_NEVILLE_API AGuyStart : public AActor, public IGuyStartReturns
{
	GENERATED_BODY()

public:
	AGuyStart();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AP_Guy> _MyGuy;
	
public:
	virtual TSubclassOf<AP_Guy> Return_GuyClass_Implementation() override;
};
