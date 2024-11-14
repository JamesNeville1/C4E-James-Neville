#include "FloorButton.h"

#include "ButtonComponent.h"
#include "C4E_Neville/Guys/P_Guy.h"
#include "C4E_Neville/Guys/P_Guy_Lil.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

AFloorButton::AFloorButton()
{
	PrimaryActorTick.bCanEverTick = false;

	_Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	RootComponent = _Collider;

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_Mesh -> SetupAttachment(_Collider);
}

void AFloorButton::Handle_OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(UKismetMathLibrary::ClassIsChildOf(OtherActor->GetClass(), AP_Guy::StaticClass()))
	{
		_UseCount++;
		if(_UseCount == 1)
		{
			_Mesh->SetMaterial(0, _ButtonComponent->_OnMaterial);
			_ButtonComponent->Press();
		}
	}
}

void AFloorButton::Handle_OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(UKismetMathLibrary::ClassIsChildOf(OtherActor->GetClass(), AP_Guy::StaticClass()))
	{
		_UseCount--;
		if(_UseCount == 0)
		{
			_Mesh->SetMaterial(0, _ButtonComponent->_OffMaterial);
			_ButtonComponent->UnPress();
		}
	}
}

void AFloorButton::BeginPlay()
{
	_ButtonComponent = FindComponentByClass<UButtonComponent>();

	if (_ButtonComponent == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Floor Button Needs 'ButtonComponent'!"));
	}

	_Collider->OnComponentBeginOverlap.AddUniqueDynamic(this, &AFloorButton::Handle_OnOverlap);
	_Collider->OnComponentEndOverlap.AddUniqueDynamic(this, &AFloorButton::Handle_OnOverlapEnd);
	
	Super::BeginPlay();
}

