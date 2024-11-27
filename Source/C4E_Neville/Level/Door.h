// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C4E_Neville/Interface/LevelPiece.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

class UBoxComponent;

UCLASS()
class C4E_NEVILLE_API ADoor : public AActor, public ILevelPiece
{
	GENERATED_BODY()

public:
	ADoor();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> _Collider;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> _Mesh;

	virtual void BeginPlay() override;

	virtual void Trigger_Implementation() override;
	virtual void Reverse_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector _EndPos;
};
