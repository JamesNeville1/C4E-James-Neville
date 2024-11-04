#include "P_Guy.h"

#include "ToolBuilderUtil.h"
#include "C4E_Neville/ClassStuff/HealthComponent.h"
#include "C4E_Neville/Controller/PC_Guy.h"
#include "C4E_Neville/GameMode/GM_Puzzle.h"
#include "C4E_Neville/Interface/UseOnOverlap.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

AP_Guy::AP_Guy()
{
	PrimaryActorTick.bCanEverTick = false;

	_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_Camera->SetupAttachment(RootComponent);
	
	_Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

void AP_Guy::BeginPlay()
{
	_Health->OnDead.AddUniqueDynamic(this, &AP_Guy::Handle_HealthComponentDead);
	_Health->OnDamaged.AddUniqueDynamic(this, &AP_Guy::Handle_HealthComponentDamaged);
	//GetCapsuleComponent()->OnComponentBeginOverlap(this, &AP_Guy::Handle_OnOverlap);
	
	Super::BeginPlay();
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

UInputMappingContext* AP_Guy::GetMappingContext_Implementation()
{
	return  _InputMapping;
}

AP_Guy* AP_Guy::Return_Self_Implementation()
{
	return this;
}

void AP_Guy::OnSwapGuyInit(APC_Guy* controller)
{
	OnSwapGuy.AddUniqueDynamic(controller, &APC_Guy::SwapCharacter);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("AAAAAAAAAAAAAAAAAAAAA"));
}

void AP_Guy::Handle_HealthComponentDead(AController* causer)
{
}

void AP_Guy::Handle_HealthComponentDamaged(float newHealth, float maxHealth, float change)
{
}

void AP_Guy::Handle_OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IUseOnOverlap::Execute_Interact(OtherActor);
}

