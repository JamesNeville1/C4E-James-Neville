// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C4E_Neville/Interface/LevelPiece.h"
#include "GameFramework/Actor.h"
#include "LaunchPad.generated.h"

class AP_Guy;
class UBoxComponent;

UCLASS()
class C4E_NEVILLE_API ALaunchPad : public AActor, public ILevelPiece
{
	GENERATED_BODY()

public:
	ALaunchPad();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> _Collider;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> _Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> _OverlapZone;
	
	virtual void BeginPlay() override;

	virtual void Trigger_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float _Velocity;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AActor*> _Held;

	
	UFUNCTION(BlueprintCallable)
	void Handle_OnOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION(BlueprintCallable)
	void Handle_OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Launch")
	void RecieveTrigger();
};
