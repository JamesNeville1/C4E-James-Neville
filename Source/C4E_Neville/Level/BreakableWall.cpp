#include "BreakableWall.h"

#include "C4E_Neville/ClassStuff/HealthComponent.h"
#include "Components/BoxComponent.h"

ABreakableWall::ABreakableWall()
{
	PrimaryActorTick.bCanEverTick = false;

	_Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	RootComponent = _Collider;

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_Mesh -> SetupAttachment(_Collider);
}

void ABreakableWall::BeginPlay()
{
	Super::BeginPlay();

	_Health = FindComponentByClass<UHealthComponent>();

	if(_Health == nullptr)
	{
		//Create
		_Health = NewObject<UHealthComponent>(this, TEXT("Health"));
		AddInstanceComponent(_Health);

		//Register
		_Health->RegisterComponent();
		Modify();
	}

	_Health->OnDead.AddUniqueDynamic(this, &ABreakableWall::Handle_OnDeath);
}

void ABreakableWall::Handle_OnDeath(AController* causer)
{

	Destroy();
}

