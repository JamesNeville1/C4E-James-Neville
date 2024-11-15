#include "LevelEnd.h"

#include "C4E_Neville/Guys/P_Guy.h"
#include "C4E_Neville/Interface/GuyReturns.h"
#include "Components/BoxComponent.h"

ALevelEnd::ALevelEnd()
{
	PrimaryActorTick.bCanEverTick = false;

	_Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	RootComponent = _Collider;

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_Mesh -> SetupAttachment(_Collider);

	_OverlapZone = CreateDefaultSubobject<UBoxComponent>(TEXT("Overlap Zone"));
	_OverlapZone -> SetupAttachment(_Collider);
}

TSubclassOf<AP_Guy> ALevelEnd::Return_GuyClass_Implementation()
{
	return _MyGuy;
}

void ALevelEnd::Handle_OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AP_Guy* guy = IGuyReturns::Execute_Return_Self(OtherActor);

	if(guy == nullptr) return;
	if (guy->GetClass() != _MyGuy) return;

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("On Finish"));
}

void ALevelEnd::Handle_OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AP_Guy* guy = IGuyReturns::Execute_Return_Self(OtherActor);

	if(guy == nullptr) return;
	if (guy->GetClass() != _MyGuy) return;

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("Off Finish"));
}

void ALevelEnd::BeginPlay()
{
	Super::BeginPlay();

	_OverlapZone->OnComponentBeginOverlap.AddUniqueDynamic(this, &ALevelEnd::Handle_OnOverlap);
	_OverlapZone->OnComponentEndOverlap.AddUniqueDynamic(this, &ALevelEnd::Handle_OnOverlapEnd);
}

