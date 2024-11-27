// Fill out your copyright notice in the Description page of Project Settings.


#include "PC_FPS.h"

#include "EnhancedInputComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include  "EnhancedInputSubsystems.h"
#include "HealthComponent.h"
#include "Inputable.h"
#include "P_FPS.h"
#include "Widget_Hud.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/KismetMathLibrary.h"

void APC_FPS::SetupInputComponent()
{
	Super::SetupInputComponent();


	if (UEnhancedInputComponent* EIP = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EIP->BindAction(_LookAction, ETriggerEvent::Triggered, this, &APC_FPS::Look);
		EIP->BindAction(_MoveAction, ETriggerEvent::Triggered, this, &APC_FPS::Move);
		EIP->BindAction(_JumpAction, ETriggerEvent::Triggered, this, &APC_FPS::JumpPressed);
		EIP->BindAction(_JumpAction, ETriggerEvent::Completed, this, &APC_FPS::JumpReleased);
		EIP->BindAction(_FireAction, ETriggerEvent::Started, this, &APC_FPS::FirePressed);
		EIP->BindAction(_FireAction, ETriggerEvent::Completed, this, &APC_FPS::FireReleased);
	}
}

void APC_FPS::Look(const FInputActionValue& value)
{
	FVector2D LookVector = value.Get<FVector2d>();

	if (APawn* currentpawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(currentpawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_Look(currentpawn, LookVector);
		}
	}
}

void APC_FPS::Move(const FInputActionValue& value)
{
	FVector2D MoveVector = value.Get<FVector2d>();

	if (APawn* currentpawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(currentpawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_Move(currentpawn, MoveVector);
		}
	}
}

void APC_FPS::JumpPressed()
{
	if (APawn* currentpawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(currentpawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_JumpPressed(currentpawn);
		}
	}
}

void APC_FPS::JumpReleased()
{
	if (APawn* currentpawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(currentpawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_JumpReleased(currentpawn);
		}
	}
}

void APC_FPS::FirePressed()
{
	if (APawn* currentpawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(currentpawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_FirePressed(currentpawn);
		}
	}
}

void APC_FPS::FireReleased()
{
	if (APawn* currentpawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(currentpawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_FireReleased(currentpawn);
		}
	}
}

void APC_FPS::BeginPlay()
{
	Super::BeginPlay();

	if (_HudWidgetClass)
	{
		_HudWidget = CreateWidget<UWidget_Hud, APC_FPS*>(this, _HudWidgetClass.Get());
		_HudWidget->AddToViewport();

		_player = Cast<AP_FPS>(GetCharacter());
		_HudWidget->UpdateHealth(1.0f);
		_HudWidget->UpdateScore(0);
	}
}

void APC_FPS::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		if (UKismetSystemLibrary::DoesImplementInterface(InPawn, UInputable::StaticClass()))
		{
			subsystem->AddMappingContext(IInputable::Execute_GetMappingContext(InPawn), 0);

			//UI Test
			if (_HudWidget)
			{
				_player = Cast<AP_FPS>(GetCharacter());
				_HudWidget->UpdateHealth(.01f);
				_HudWidget->UpdateScore(_player->_Points);

				//_player->_OnPlayerDamage.AddUniqueDynamic(_HudWidget, UWidget_Hud::UpdateHealth())
			}
		}
	}
}
