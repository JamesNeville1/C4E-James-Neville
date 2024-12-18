﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inputable.h"
#include "GameFramework/Character.h"
#include "P_FPS.generated.h"

class AWeapon_Base;
class UHealthComponent;
class UCameraComponent;
class UCharacterMovementComponent;
class UCapsuleComponent;

DECLARE_DYNAMIC_DELEGATE_RetVal(int, FOnPlayerDamageSignature);

UCLASS()
class C4E_NEVILLE_API AP_FPS : public ACharacter, public IInputable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AP_FPS();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Input_Look_Implementation(FVector2D value) override;
	virtual void Input_Move_Implementation(FVector2D value) override;
	virtual void Input_JumpPressed_Implementation() override;
	virtual void Input_JumpReleased_Implementation() override;
	virtual void Input_FirePressed_Implementation() override;
	virtual void Input_FireReleased_Implementation() override;

	virtual UInputMappingContext* GetMappingContext_Implementation() override;

	int GetHealth();

	int _Points;

	FOnPlayerDamageSignature _OnPlayerDamage;

	UFUNCTION()
	void DamageTest();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> _Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UHealthComponent> _Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInputMappingContext> _InputMapping;


	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USceneComponent> _WeaponAttachPoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AWeapon_Base> _DefaultWeapon;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<AWeapon_Base> _WeaponRef;

	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UFUNCTION()
	void Handle_HealthComponentDead(AController* causer);
	UFUNCTION()
	void Handle_HealthComponentDamaged(float newHealth, float maxHealth, float change);
};
