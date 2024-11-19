// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C4E_Neville/Interface/UseOnOverlap.h"
#include "Components/ActorComponent.h"
#include "CandyComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCandyEatenSignature, FVector, pos);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class C4E_NEVILLE_API UCandyComponent : public UActorComponent, public IUseOnOverlap
{
	GENERATED_BODY()

public:
	UCandyComponent();

	FOnCandyEatenSignature _OnCandyEaten;

protected:
	virtual void BeginPlay() override;
	virtual void Interact_Implementation() override;
	
private:
};
