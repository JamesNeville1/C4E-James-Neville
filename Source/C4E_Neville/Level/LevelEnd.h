// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C4E_Neville/Interface/GuyStaticClassReturn.h"
#include "GameFramework/Actor.h"
#include "LevelEnd.generated.h"

class UBoxComponent;

UCLASS()
class C4E_NEVILLE_API ALevelEnd : public AActor, public IGuyStaticClassReturn
{
	GENERATED_BODY()

public:
	ALevelEnd();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AP_Guy> _MyGuy;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UBoxComponent> _Collider;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> _Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UBoxComponent> _OverlapZone;
	
	virtual TSubclassOf<AP_Guy> Return_GuyClass_Implementation() override;

	UFUNCTION(BlueprintCallable)
	void Handle_OnOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION(BlueprintCallable)
	void Handle_OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

protected:
	virtual void BeginPlay() override;

};
