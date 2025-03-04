﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "Kismet/KismetMathLibrary.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	_MaxHealth = 100;
}


void UHealthComponent::Reset()
{
	_CurrentHealth = _MaxHealth;
}

float UHealthComponent::GetNormalisedHealth()
{
	return UKismetMathLibrary::NormalizeToRange(_CurrentHealth, 0, _MaxHealth);
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	_CurrentHealth = _MaxHealth;
	GetOwner()->OnTakeAnyDamage.AddUniqueDynamic(this, &UHealthComponent::DamageTaken);
}

void UHealthComponent::DamageTaken(AActor* damagedActor, float damage, const UDamageType* damageType,
                                   AController* instigator, AActor* causer)
{
	if (!_Invincible)
	{
		const float changeBy = FMath::Min(_CurrentHealth, damage);
		_CurrentHealth -= changeBy;

		OnDamaged.Broadcast(_CurrentHealth, _MaxHealth, changeBy);
		//UE_LOG(LogTemp, Display, TEXT("Damage for %f, %f health remaing"), changeBy, _CurrentHealth);

		if (_CurrentHealth <= 0.0f)
		{
			//UE_LOG(LogTemp, Display, TEXT("DEADED"));
			OnDead.Broadcast(instigator);
		}
	}
}
