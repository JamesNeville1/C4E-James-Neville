#include "LevelEnd.h"

#include "C4E_Neville/GameMode/LevelManager.h"
#include "C4E_Neville/Guys/P_Guy.h"
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
	if (OtherActor->GetClass() != _MyGuy) return;

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("On Finish"));
	OnStateOn.Broadcast();

	RecieveOnOverlap();
}

void ALevelEnd::Handle_OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->GetClass() != _MyGuy) return;

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("Off Finish"));
	OnStateOff.Broadcast();

	RecieveOnOverlapEnd();
}

void ALevelEnd::Register(ALevelManager* levelManager)
{
	_OverlapZone->OnComponentBeginOverlap.AddUniqueDynamic(this, &ALevelEnd::Handle_OnOverlap);
	_OverlapZone->OnComponentEndOverlap.AddUniqueDynamic(this, &ALevelEnd::Handle_OnOverlapEnd);

	OnStateOn.AddUniqueDynamic(levelManager, &ALevelManager::EndLevelCounterIncrease);
	OnStateOff.AddUniqueDynamic(levelManager, &ALevelManager::EndLevelCounterDecrease);

	_OverlapZone->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	_Mesh->SetMaterial(0, _OffMaterial);
}

void ALevelEnd::Enable()
{
	_OverlapZone->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	_Mesh->SetMaterial(0, _OnMaterial);

	RecieveEnable();
}

//Hooks
void ALevelEnd::RecieveEnable_Implementation()
{
}

void ALevelEnd::RecieveOnOverlap_Implementation()
{
}

void ALevelEnd::RecieveOnOverlapEnd_Implementation()
{
}

