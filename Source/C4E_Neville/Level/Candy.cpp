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
	_Collider->OnComponentBeginOverlap.AddUniqueDynamic(this, &ACandy::OnOverlap);
	
	Super::BeginPlay();
}

void ACandy::OnOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("AAAAAAAAAAAAAAAAAAAAA"));
}
