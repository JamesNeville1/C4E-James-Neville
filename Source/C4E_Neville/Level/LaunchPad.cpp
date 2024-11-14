#include "LaunchPad.h"

#include "C4E_Neville/Guys/P_Guy.h"
#include "C4E_Neville/Interface/GuyReturns.h"
#include "Components/BoxComponent.h"


ALaunchPad::ALaunchPad()
{
	PrimaryActorTick.bCanEverTick = false;

	_Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	RootComponent = _Collider;

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_Mesh -> SetupAttachment(_Collider);

	_OverlapZone = CreateDefaultSubobject<UBoxComponent>(TEXT("Overlap"));
	_OverlapZone -> SetupAttachment(_Collider);
}

void ALaunchPad::BeginPlay()
{
	Super::BeginPlay();

	_OverlapZone->OnComponentBeginOverlap.AddUniqueDynamic(this, &ALaunchPad::Handle_OnOverlap);
	_OverlapZone->OnComponentEndOverlap.AddUniqueDynamic(this, &ALaunchPad::Handle_OnOverlapEnd);
}

void ALaunchPad::Trigger_Implementation()
{
	for (auto character : _HeldCharacters)
	{
		FVector dir = GetActorUpVector();
		dir *= _Velocity;
		character->LaunchCharacter(dir, false, false);
	}
}

void ALaunchPad::Handle_OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AP_Guy* guy = IGuyReturns::Execute_Return_Self(OtherActor);

	if(guy == nullptr) return;
	
	_HeldCharacters.AddUnique(guy);
}

void ALaunchPad::Handle_OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AP_Guy* guy = IGuyReturns::Execute_Return_Self(OtherActor);

	if(guy == nullptr) return;
	
	_HeldCharacters.Remove(guy);
}

