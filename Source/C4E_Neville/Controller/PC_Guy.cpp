#include "PC_Guy.h"

#include "EnhancedInputComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include  "EnhancedInputSubsystems.h"
#include "C4E_Neville/ClassStuff/HealthComponent.h"
#include "C4E_Neville/Guys/P_Guy.h"
#include "C4E_Neville/Guys/P_Guy_Big.h"
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

	TArray<TSubclassOf<AP_Guy>> guyKeys;
	_GuyMap.GenerateKeyArray(guyKeys);

	int index = guyKeys.Find(player->GetClass()->GetSuperClass());

	index > guyKeys.Num() - 2 ? index = 0 : index++;
	
	Possess(_GuyMap[guyKeys[index]]);
}

void APC_Guy::ControllerSetup(TArray<TSubclassOf<AP_Guy>> swapOrder, TArray<AP_Guy*> guys, int sharedLivesTotal, bool bigGuyCanThrow) //ToDo: Use Guy Array Param
{	
	GuySwapSetup(swapOrder, guys);

	Cast<AP_Guy_Big>(_GuyMap[AP_Guy_Big::StaticClass()])->SetCanThrow(bigGuyCanThrow);
	
	_SharedLivesCurrent = sharedLivesTotal;
}

void APC_Guy::RespawnCheck(AP_Guy* guy)
{
	if(_SharedLivesCurrent > 0)
	{
		guy->EyeBallFramesStart();
		guy->_Health->Reset();
		_SharedLivesCurrent = _SharedLivesCurrent - 1;
	}
	else
	{
		OnOutOfLives.Broadcast(guy);
	}
}

void APC_Guy::GuySwapSetup(TArray<TSubclassOf<AP_Guy>> order, TArray<AP_Guy*> guys)
{
	//Swap Setup
	for (int i = 0; i < order.Num(); i++)
	{
		_GuyMap.Add(order[i]->GetSuperClass(), guys[i]);

		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, _GuyMap[]->GetName());
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, guys[i]->GetName());
		
		guys[i]->GuySetup(this);
	}
}
