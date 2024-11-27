#include "LaunchPad.h"

#include "C4E_Neville/Interface/Launchable.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


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

void ALaunchPad::Trigger_Implementation() //ToDo: Turn Button Off Straight After
{	
	for (auto throwable : _Held)
	{
		FVector dir = GetActorUpVector();
		dir *= _Velocity;
		ILaunchable::Execute_Launch(throwable, dir);
	}
}

void ALaunchPad::Handle_OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!UKismetSystemLibrary::DoesImplementInterface(OtherActor, ULaunchable::StaticClass())) return;
	
	_Held.AddUnique(OtherActor);
}

void ALaunchPad::Handle_OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	int32 actorIndex = _Held.Find(OtherActor);
	
	if(actorIndex == INDEX_NONE) return;

	GEngine->AddOnScreenDebugMessage(-1, 10000.0f, FColor::Yellow, "aaa");
	
	_Held.RemoveAt(actorIndex);
}

