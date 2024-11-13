#include "Door.h"

#include "Components/BoxComponent.h"


ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = false;

	_Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	RootComponent = _Collider;

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_Mesh -> SetupAttachment(_Collider);
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();
}

void ADoor::Trigger_Implementation()
{
	AddActorWorldOffset(_EndPos);
}

void ADoor::Reverse_Implementation()
{
	AddActorWorldOffset(-_EndPos);
}

