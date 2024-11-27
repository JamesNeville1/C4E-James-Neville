// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "FirstActor.generated.h"

class UBoxComponent;
class UArrowComponent;

UCLASS()
class C4E_NEVILLE_API AFirstActor : public AActor
{
	GENERATED_BODY()

public:
	AFirstActor();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UBoxComponent> _Collider;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//TObjectPtr<USceneComponent> _Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> _Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UArrowComponent> _Arrow;
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//TObjectPtr<URotatingMovementComponent> _RotatingMovement;

	UFUNCTION()
	void Handle_ColliderHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                        FVector NormalImpulse, const FHitResult& Hit);

	virtual void BeginPlay() override;

	virtual ~AFirstActor() override = default;
};
