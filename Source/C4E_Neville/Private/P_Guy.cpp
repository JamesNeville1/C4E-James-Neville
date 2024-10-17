#include "P_Guy.h"

#include "GM_Puzzle.h"
#include "HealthComponent.h"
#include "ToolBuilderUtil.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

AP_Guy::AP_Guy()
{
	PrimaryActorTick.bCanEverTick = false;

	_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_Camera->SetupAttachment(RootComponent);
	
	_Health = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	
	//So we can actually look left and right, your welcome designers ;-;
	bUseControllerRotationYaw = false; //Doesn't work?
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AP_Guy::BeginPlay()
{
	Super::BeginPlay();

	_Health->OnDead.AddUniqueDynamic(this, &AP_Guy::Handle_HealthComponentDead);
	_Health->OnDamaged.AddUniqueDynamic(this, &AP_Guy::Handle_HealthComponentDamaged);

	OnSwapGuy.AddUniqueDynamic(Cast<AGM_Puzzle>(UGameplayStatics::GetGameMode(GetWorld())), &AGM_Puzzle::SwapCharacter); //ToDo: Why multi
}

void AP_Guy::Input_Look_Implementation(FVector2D value)
{
	//UE_LOG(LogTemp, Display, TEXT("X: %f, Y: %f"), value.X, value.Y);
	
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
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Special Logic Here!"));
	SpecialLogic();
	//ToDo: Special Logic
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

void AP_Guy::SpecialLogic() //ToDo:?
{
	
}

void AP_Guy::Handle_HealthComponentDead(AController* causer)
{
}

void AP_Guy::Handle_HealthComponentDamaged(float newHealth, float maxHealth, float change)
{
}

