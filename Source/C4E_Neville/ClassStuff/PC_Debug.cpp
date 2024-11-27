// Fill out your copyright notice in the Description page of Project Settings.


#include "PC_Debug.h"

#include <string>

#include "EnhancedInputComponent.h"

void APC_Debug::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EIP = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EIP->BindAction(_DebugAction, ETriggerEvent::Triggered, this, &APC_Debug::Debug);
		EIP->BindAction(_JumpAction, ETriggerEvent::Started, this, &APC_Debug::Jump);
		EIP->BindAction(_MoveXAction, ETriggerEvent::Started, this, &APC_Debug::MoveX);
		EIP->BindAction(_MoveYAction, ETriggerEvent::Started, this, &APC_Debug::MoveY);
		EIP->BindAction(_SprintAction, ETriggerEvent::Started, this, &APC_Debug::Sprint);
		EIP->BindAction(_SpecialAction, ETriggerEvent::Started, this, &APC_Debug::Special);
		EIP->BindAction(_LookAction, ETriggerEvent::Started, this, &APC_Debug::Look);
	}
}

void APC_Debug::Debug(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("I Work!"));
}

void APC_Debug::Jump(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("Beans!"));
}

void APC_Debug::MoveX(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("X: %f"), Value[0]);
}

void APC_Debug::MoveY(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("Y: %f"), Value[0]);
}

void APC_Debug::Sprint(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("Cheese!"));
}

void APC_Debug::Special(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Display, TEXT("KABOOM!"));
}

void APC_Debug::Look(const FInputActionValue& Value)
{
	//Learn how to merge?
	UE_LOG(LogTemp, Display, TEXT("Look X: %f"), Value[0]);
	UE_LOG(LogTemp, Display, TEXT("Look Y: %f"), Value[1]);
}
