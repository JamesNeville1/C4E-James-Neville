// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthComponentDeadSignature, AController*, causer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FHealthComponentDamageSignature, float, newHealth, float, maxHealth, float, change);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class C4E_NEVILLE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHealthComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool _Invincible;

	UPROPERTY(BlueprintAssignable)
	FHealthComponentDeadSignature OnDead;
	UPROPERTY(BlueprintAssignable)
	FHealthComponentDamageSignature OnDamaged;

	//Moved from protected
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _MaxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float _CurrentHealth;

	UFUNCTION()
	void Reset();
	
protected:
	
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void DamageTaken(AActor* damagedActor, float damage, const UDamageType* damageType, AController* instigator, AActor* causer);
};
