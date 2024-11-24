#include "P_Guy.h"

#include "../Level/CandyComponent.h"
#include "C4E_Neville/ClassStuff/HealthComponent.h"
#include "C4E_Neville/Controller/PC_Guy.h"
#include "C4E_Neville/Interface/UseOnOverlap.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AP_Guy::AP_Guy()
{
	PrimaryActorTick.bCanEverTick = false;

	_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_Camera->SetupAttachment(RootComponent);
	
	_Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

#pragma region Input

void AP_Guy::Input_Look_Implementation(FVector2D value)
{
	AddActorWorldRotation(FRotator(0.0f, value.X, 0.0f));
	_Camera->AddLocalRotation(FRotator(value.Y, 0, 0));

	RecieveInput_Look(value);
}
void AP_Guy::Input_Move_Implementation(FVector2D value)
{
	AddMovementInput(FVector::VectorPlaneProject(_Camera->GetForwardVector(),
		FVector::UpVector).GetSafeNormal(), value.X);
	AddMovementInput(_Camera->GetRightVector(), value.Y);

	RecieveInput_Move(value);
}

void AP_Guy::Input_MovePressed_Implementation()
{
	GetWorld()->GetTimerManager().SetTimer(_FootstepTimer, this, &AP_Guy::PlayFootstep, _TimeBetweenSteps, true);

	RecieveInput_MovePressed();
}

void AP_Guy::Input_MoveReleased_Implementation()
{
	if(_FootstepTimer.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(_FootstepTimer);
	}

	RecieveInput_MoveReleased();
}

void AP_Guy::Input_JumpPressed_Implementation()
{
	ACharacter::Jump();

	RecieveInput_JumpPressed();
}


void AP_Guy::Input_JumpReleased_Implementation()
{
	ACharacter::StopJumping();

	RecieveInput_JumpReleased();
}

void AP_Guy::Input_SpecialPressed_Implementation()
{
	if(_CanSpecial)
	{
		SpecialLogic();
	}
	else
	{
		
	}

	RecieveInput_SpecialPressed();
}

void AP_Guy::Input_CharacterSwapPressed_Implementation()
{
	OnSwapGuy.Broadcast();

	RecieveInput_CharacterSwapPressed();
}

UInputMappingContext* AP_Guy::GetMappingContext_Implementation()
{
	return  _InputMapping;
}

#pragma endregion Input

#pragma region Footstep Logic

void AP_Guy::PlayFootstep()
{
	if(!GetCharacterMovement()->IsFalling())
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), _FootstepSFX, GetActorLocation());
	}
}


#pragma endregion Footstep Logic

#pragma region Pawn Overrides

void AP_Guy::UnPossessed()
{
	Super::UnPossessed();

	if(_FootstepTimer.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(_FootstepTimer);
	}
}

#pragma endregion Pawn Overrides

#pragma region Setup

void AP_Guy::GuySetup(APC_Guy* controller)
{
	OnSwapGuy.AddUniqueDynamic(controller, &APC_Guy::SwapCharacter);
	OnRespawnAlertCheck.AddUniqueDynamic(controller, &APC_Guy::RespawnCheck);
	OnDamageUIAlert.AddUniqueDynamic(controller, &APC_Guy::UpdateHealthAlert);

	_Health->OnDead.AddUniqueDynamic(this, &AP_Guy::Handle_HealthComponentDead);
	_Health->OnDamaged.AddUniqueDynamic(this, &AP_Guy::Handle_HealthComponentDamaged);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddUniqueDynamic(this, &AP_Guy::Handle_OnOverlap);
}

#pragma endregion Setup

#pragma region Health Functions

void AP_Guy::ResetHealth()
{
	_Health->Reset();
}

float AP_Guy::GetNormalizedHealth()
{
	return _Health->GetNormalisedHealth();
}

FLinearColor AP_Guy::GetHealthColor()
{
	return _HealthColor;
}

#pragma endregion Health Functions

#pragma region Utils

FHitResult AP_Guy::LineTraceLogic(FName profile, float range)
{
	FVector start = _Camera->GetComponentLocation();

	FVector	end = UKismetMathLibrary::GetForwardVector(_Camera->GetComponentRotation());
	end *= range;
	end += start;


	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Add(this);
	FHitResult hitResult;

	UKismetSystemLibrary::LineTraceSingleByProfile(
		GetWorld(), start, end, profile,
		false, actorsToIgnore, EDrawDebugTrace::Persistent, hitResult, true);

	return  hitResult;
}

void AP_Guy::SpecialLogic()
{
}


#pragma endregion Utils

#pragma region Component Event Handles

void AP_Guy::Handle_HealthComponentDead(AController* causer)
{
	OnRespawnAlertCheck.Broadcast(this);
}

void AP_Guy::Handle_HealthComponentDamaged(float newHealth, float maxHealth, float change)
{
	if(GetController() != nullptr)
	{
		OnDamageUIAlert.Broadcast(_Health->GetNormalisedHealth(), _HealthColor);
	}
}

void AP_Guy::Handle_OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("Overlap Hit Something"));
	UActorComponent* candyComponent = OtherActor->GetComponentByClass(UCandyComponent::StaticClass());

	if(IsValid(candyComponent))
	{
		IUseOnOverlap::Execute_Interact(candyComponent);
	}
	
}

#pragma endregion Component Event Handles

#pragma region Eye Ball Frames

void AP_Guy::EyeBallFramesStart()
{
	_Health->_Invincible = true;

	GetWorld()->GetTimerManager().SetTimer(_EyeBallTimerHandle, this, &AP_Guy::EyeBallFramesStop, _EyeBallFrameLength, false);
}

void AP_Guy::EyeBallFramesStop()
{
	_Health->_Invincible = false;
}
#pragma endregion Eye Ball Frames

#pragma region Designer Hooks

void AP_Guy::RecievePlayFootstep_Implementation() { }
void AP_Guy::RecieveInput_Look_Implementation(const FVector2D& value) { }
void AP_Guy::RecieveInput_Move_Implementation(const FVector2D& value) { }
void AP_Guy::RecieveInput_MovePressed_Implementation() { }
void AP_Guy::RecieveInput_MoveReleased_Implementation() { }
void AP_Guy::RecieveInput_JumpPressed_Implementation() { }
void AP_Guy::RecieveInput_JumpReleased_Implementation() { }
void AP_Guy::RecieveInput_SpecialPressed_Implementation() { }
void AP_Guy::RecieveInput_CharacterSwapPressed_Implementation() { }

#pragma endregion Designer Hooks
