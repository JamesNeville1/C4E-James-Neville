// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ButtonComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class C4E_NEVILLE_API UButtonComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UButtonComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<AActor*> _LevelPieces;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterialInstance* _OnMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterialInstance* _OffMaterial;

	UFUNCTION()
	void Press();
	UFUNCTION()
	void UnPress();
};
