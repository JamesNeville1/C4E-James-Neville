#include "P_Guy.h"

#include "ToolBuilderUtil.h"
#include "C4E_Neville/ClassStuff/HealthComponent.h"
#include "C4E_Neville/Controller/PC_Guy.h"
#include "../Level/CandyComponent.h"
#include "C4E_Neville/GameMode/GM_Puzzle.h"
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

void AP_Guy::Input_Look_Implementation(FVector2D value)
{
	AddActorWorldRotation(FRotator(0.0f, value.X, 0.0f));
	_Camera->AddLocalRotation(FRotator(value.Y, 0, 0));
}

void AP_Guy::Input_Move_Implementation(FVector2D value)
{
	AddMovementInput(FVector::VectorPlaneProject(_Camera->GetForwardVector(),
		FVector::UpVector).GetSafeNormal(), value.X);
	AddMovementInput(_Camera->GetRightVector(), value.Y);
}

void AP_Guy::Input_MovePressed_Implementation()
{
	GetWorld()->GetTimerManager().SetTimer(_FootstepTimer, this, &AP_Guy::PlayFootStep, _TimeBetweenSteps, true);
}

void AP_Guy::PlayFootStep()
{
	if(!GetCharacterMovement()->IsFalling())
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), _FootstepSFX, GetActorLocation());
	}
}

void AP_Guy::Input_MoveReleased_Implementation()
{
	if(_FootstepTimer.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(_FootstepTimer);
	}
}

void AP_Guy::Input_JumpPressed_Implementation()
{
	ACharacter::Jump();
}


void AP_Guy::Input_JumpReleased_Implementation()
{
	ACharacter::StopJumping();
}

void AP_Guy::Input_SpecialPressed_Implementation()
{
	SpecialLogic();
}

void AP_Guy::Input_CharacterSwapPressed_Implementation()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("Swap Logic Here!"));
	OnSwapGuy.Broadcast();
}

void AP_Guy::UnPossessed()
{
	Super::UnPossessed();

	if(_FootstepTimer.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(_FootstepTimer);
	}
}

UInputMappingContext* AP_Guy::GetMappingContext_Implementation()
{
	return  _InputMapping;
}

AP_Guy* AP_Guy::Return_Self_Implementation()
{
	return this;
}

void AP_Guy::GuySetup(APC_Guy* controller)
{
	OnSwapGuy.AddUniqueDynamic(controller, &APC_Guy::SwapCharacter);
	OnRespawnAlertCheck.AddUniqueDynamic(controller, &APC_Guy::RespawnCheck);
	OnDamageUIAlert.AddUniqueDynamic(controller, &APC_Guy::UpdateHealthAlert);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("AAAAAAAAAAAAAAAAAAAAA"));

	_Health->OnDead.AddUniqueDynamic(this, &AP_Guy::Handle_HealthComponentDead);
	_Health->OnDamaged.AddUniqueDynamic(this, &AP_Guy::Handle_HealthComponentDamaged);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddUniqueDynamic(this, &AP_Guy::Handle_OnOverlap);

	//GetWorld()->GetOnBeginPlayEvent().AddUObject(this, &AP_Guy::LateBeginPlay);
	
	//Super::BeginPlay();
}



FHitResult AP_Guy::SpecialLineTraceLogic(FName profile, float range)
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
	OnSpecialLogic.Broadcast();
}

void AP_Guy::Handle_HealthComponentDead(AController* causer)
{
	OnRespawnAlertCheck.Broadcast(this);
}

void AP_Guy::Handle_HealthComponentDamaged(float newHealth, float maxHealth, float change)
{
	if(GetController() != nullptr)
	{
		OnDamageUIAlert.Broadcast(_Health->GetNormalisedHealth(), _HealthColour);
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

void AP_Guy::EyeBallFramesStart()
{
	_Health->_Invincible = true;

	GetWorld()->GetTimerManager().SetTimer(_EyeBallTimerHandle, this, &AP_Guy::EyeBallFramesStop, _EyeBallFrameLength, false);
}

void AP_Guy::EyeBallFramesStop()
{
	_Health->_Invincible = false;
}

