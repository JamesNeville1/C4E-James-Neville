// Fill out your copyright notice in the Description page of Project Settings.


#include "P_FPS.h"

#include "HealthComponent.h"
#include "Camera/CameraComponent.h"


// Sets default values
AP_FPS::AP_FPS()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_Camera->SetupAttachment(RootComponent);
	_Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));

	
}

// Called when the game starts or when spawned
void AP_FPS::BeginPlay()
{
	Super::BeginPlay();

	_Health->OnDead.AddUniqueDynamic(this, &AP_FPS::Handle_HealthComponentDead);
	_Health->OnDamaged.AddUniqueDynamic(this, &AP_FPS::Handle_HealthComponentDamaged );
}

void AP_FPS::Input_Look_Implementation(FVector2D value)
{
	//IInputable::Input_Look_Implementation(value);
	UE_LOG(LogTemp, Display, TEXT("X: %f, Y: %f"), value.X, value.Y);
	
	AddActorWorldRotation(FRotator(0, value.X * 100, 0));
	_Camera->AddLocalRotation(FRotator(value.Y, 0, 0));
}

void AP_FPS::Input_Move_Implementation(FVector2D value)
{
	//IInputable::Input_Move_Implementation(value);

	AddMovementInput(FVector::VectorPlaneProject(_Camera->GetForwardVector(),
		FVector::UpVector).GetSafeNormal(), value.Y);
	AddMovementInput(_Camera->GetRightVector(), value.X);
}

void AP_FPS::Input_JumpPressed_Implementation()
{
	//IInputable::Input_JumpPressed_Implementation();
	ACharacter::Jump();
}

void AP_FPS::Input_JumpReleased_Implementation()
{
	//IInputable::Input_JumpReleased_Implementation();
	ACharacter::StopJumping();
}

void AP_FPS::Input_FirePressed_Implementation()
{
	IInputable::Input_FirePressed_Implementation();
}

void AP_FPS::Input_FireReleased_Implementation()
{
	IInputable::Input_FireReleased_Implementation();
}

UInputMappingContext* AP_FPS::GetMappingContext_Implementation()
{
	//return IInputable::GetMappingContext_Implementation();
	return  _InputMapping;
}

void AP_FPS::Handle_HealthComponentDead(AController* causer)
{
	
}

void AP_FPS::Handle_HealthComponentDamaged(float newHealth, float maxHealth, float change)
{
	
}

