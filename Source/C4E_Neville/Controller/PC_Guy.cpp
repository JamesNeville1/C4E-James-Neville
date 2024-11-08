#include "PC_Guy.h"

#include "EnhancedInputComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include  "EnhancedInputSubsystems.h"
#include "C4E_Neville/Guys/P_Guy.h"
#include "C4E_Neville/Interface/GuyInputable.h"
#include "C4E_Neville/Interface/GuyReturns.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

void APC_Guy::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(UEnhancedInputComponent* EIP = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EIP->BindAction(_LookAction, ETriggerEvent::Triggered, this, &APC_Guy::Look);
		EIP->BindAction(_MoveAction, ETriggerEvent::Triggered, this, &APC_Guy::Move);
		EIP->BindAction(_JumpAction, ETriggerEvent::Triggered, this, &APC_Guy::JumpPressed);
		EIP->BindAction(_JumpAction, ETriggerEvent::Completed, this, &APC_Guy::JumpReleased);
		EIP->BindAction(_SpecialAction, ETriggerEvent::Started, this, &APC_Guy::SpecialPressed);
		EIP->BindAction(_CharacterSwapAction, ETriggerEvent::Started, this, &APC_Guy::CharacterSwapPressed);
	}
}

void APC_Guy::Look(const FInputActionValue& value)
{
	FVector2D LookVector = value.Get<FVector2d>();

	if(APawn* currentpawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentpawn, UGuyInputable::StaticClass()))
		{
			IGuyInputable::Execute_Input_Look(currentpawn, LookVector);
		}
	}
}

void APC_Guy::Move(const FInputActionValue& value)
{
	FVector2D MoveVector = value.Get<FVector2d>();

	if(APawn* currentpawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentpawn, UGuyInputable::StaticClass()))
		{
			IGuyInputable::Execute_Input_Move(currentpawn, MoveVector);
		}
	}
}

void APC_Guy::JumpPressed()
{
	if(APawn* currentpawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentpawn, UGuyInputable::StaticClass()))
		{
			IGuyInputable::Execute_Input_JumpPressed(currentpawn);
		}
	}
}

void APC_Guy::JumpReleased()
{
	if(APawn* currentpawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentpawn, UGuyInputable::StaticClass()))
		{
			IGuyInputable::Execute_Input_JumpReleased(currentpawn);
		}
	}
}

void APC_Guy::SpecialPressed()
{
	if(APawn* currentpawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentpawn, UGuyInputable::StaticClass()))
		{
			IGuyInputable::Execute_Input_SpecialPressed(currentpawn);
		}
	}
}

void APC_Guy::CharacterSwapPressed()
{
	if(APawn* currentpawn = GetPawn())
	{
		if(UKismetSystemLibrary::DoesImplementInterface(currentpawn, UGuyInputable::StaticClass()))
		{
			IGuyInputable::Execute_Input_CharacterSwapPressed(currentpawn);
		}
	}
}

void APC_Guy::OnPossess(APawn* InPawn)
{	
	Super::OnPossess(InPawn);
	
	if(UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if(UKismetSystemLibrary::DoesImplementInterface(InPawn, UGuyInputable::StaticClass()))
		{
			subsystem->AddMappingContext(IGuyInputable::Execute_GetMappingContext(InPawn), 0);
		}
	}
}


void APC_Guy::SwapCharacter()
{
	AP_Guy* player = IGuyReturns::Execute_Return_Self(GetCharacter());
	Possess(_SwapList[player]);
}

void APC_Guy::SwapCharacterSetup()
{
	//Swap Setup
	TArray<TSubclassOf<AP_Guy>> swapListOrderKeys;
	_SwapListOrder.GenerateKeyArray(swapListOrderKeys);

	//Setup Swap Order
	for (TSubclassOf<AP_Guy> guyClass : swapListOrderKeys)
	{
		//Get object reference from class reference map
		AP_Guy* key;
		AP_Guy* value;
		key = IGuyReturns::Execute_Return_Self(UGameplayStatics::GetActorOfClass(GetWorld(), guyClass));
		value = IGuyReturns::Execute_Return_Self(
			UGameplayStatics::GetActorOfClass(GetWorld(), _SwapListOrder[guyClass]));
		value->OnSwapGuyInit(this);
		//Add to map
		_SwapList.Add(
			key,
			value
		);
	}
}

void APC_Guy::AlertBigGuyOfSmallGuySpecial()
{
	
}
