// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C4E_Neville/Interface/LevelPiece.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

class UBoxComponent;

UCLASS()
class C4E_NEVILLE_API AMovingPlatform : public AActor, public ILevelPiece
{
	GENERATED_BODY()

public:
	AMovingPlatform();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> _Collider;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> _Mesh;

	virtual void BeginPlay() override;

	virtual void Trigger_Implementation() override;
	virtual void Reverse_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="MAIN")
	FVector _OffPos;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="MAIN")
	FVector _OnPos;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="MAIN")
	float _Speed;

	virtual void Tick(float DeltaTime) override;

private:
	FVector _TargetPos;
};
