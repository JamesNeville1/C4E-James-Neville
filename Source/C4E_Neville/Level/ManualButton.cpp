#include "ManualButton.h"

#include "ButtonComponent.h"
#include "C4E_Neville/Guys/P_Guy.h"
#include "C4E_Neville/Guys/P_Guy_Lil.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

AManualButton::AManualButton()
{
	PrimaryActorTick.bCanEverTick = false;

	_Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	RootComponent = _Collider;

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_Mesh -> SetupAttachment(_Collider);
}

void AManualButton::Handle_OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	_Pressed ? _ButtonComponent->Press() : _ButtonComponent->UnPress();

	_Pressed = !_Pressed;
}

void AManualButton::BeginPlay()
{
	_ButtonComponent = FindComponentByClass<UButtonComponent>();

	if (_ButtonComponent == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Floor Button Needs 'ButtonComponent'!"));
	}

	_Collider->OnComponentBeginOverlap.AddUniqueDynamic(this, &AManualButton::Handle_OnOverlap);

	_Pressed = true;
	
	Super::BeginPlay();
}

