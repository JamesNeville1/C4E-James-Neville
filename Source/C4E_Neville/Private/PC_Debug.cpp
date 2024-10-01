// Fill out your copyright notice in the Description page of Project Settings.


#include "C4E_Neville/Public/PC_Debug.h"

#include <string>

#include "EnhancedInputComponent.h"

void APC_Debug::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(UEnhancedInputComponent* EIP = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EIP->BindAction(_DebugAction, ETriggerEvent::Triggered, this, &APC_Debug::Debug);
		EIP->BindAction(_JumpAction, ETriggerEvent::Started, this, &APC_Debug::Jump);
	}

	
}

void APC_Debug::Debug(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Display, TEXT("I Work!"));
}

void APC_Debug::Jump(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Display, TEXT("Beans!"));
}

void APC_Debug::MoveX(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Display, TEXT("X: ", Value.ToString()));
}

void APC_Debug::MoveY(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Display, TEXT("Y: ", Value.ToString()));
}

void APC_Debug::Sprint(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Display, TEXT("Cheese!"));
}

void APC_Debug::Special(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Display, TEXT("KABOOM!"));
}

void APC_Debug::Look(const FInputActionValue& Value)
{
	//FString LookDebug = "X: " + std::to_string(Value[0]) + "Y: " + std::to_string(Value[1]);
	//UE_LOG(LogTemp, Display, TEXT(LookDebug));
}
