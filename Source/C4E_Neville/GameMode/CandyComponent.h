// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CandyComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCandyEatenSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class C4E_NEVILLE_API UCandyComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCandyComponent();

protected:
	virtual void BeginPlay() override;
	
private:
	FOnCandyEatenSignature _OnCandyEaten;
};
