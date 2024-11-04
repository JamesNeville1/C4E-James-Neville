#include "Candy.h"

#include "Components/SphereComponent.h"


ACandy::ACandy()
{
	PrimaryActorTick.bCanEverTick = false;

	_Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Root"));
	RootComponent = _Collider;

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_Mesh -> SetupAttachment(_Collider);
}



void ACandy::BeginPlay()
{
	Super::BeginPlay();
}
