// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "AIC_Pumpkin.generated.h"

class UAISenseConfig_Sight;
struct FAIStimulus;

UCLASS()
class C4E_NEVILLE_API AAIC_Pumpkin : public AAIController
{
	GENERATED_BODY()

public:
	AAIC_Pumpkin();

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAIPerceptionComponent> _AIPerception;
	TObjectPtr<UAISenseConfig_Sight> _AISense_Sight;
	
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

private:
	UFUNCTION()
	void Handle_TargetPerceptionUpdated(AActor* actor, FAIStimulus stimulus);
	UFUNCTION()
	void Handle_TargetPerceptionForgotten(AActor* actor);
};
