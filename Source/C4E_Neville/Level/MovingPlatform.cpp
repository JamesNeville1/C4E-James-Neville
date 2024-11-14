#include "MovingPlatform.h"

#include "FrameTypes.h"
#include "Components/BoxComponent.h"
#include "Kismet/BlueprintTypeConversions.h"
#include "Kismet/KismetMaterialLibrary.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	_Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	RootComponent = _Collider;

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_Mesh -> SetupAttachment(_Collider);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(false);
}

void AMovingPlatform::Trigger_Implementation()
{
	_TargetPos = _OnPos;
	SetActorTickEnabled(true);
}

void AMovingPlatform::Reverse_Implementation()
{
	_TargetPos = _OffPos;
	SetActorTickEnabled(true);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	FVector step = FMath::VInterpTo(GetActorLocation(), _TargetPos, DeltaTime, _Speed);
	SetActorLocation(step);
	
	if(GetActorLocation() == _TargetPos)
	{
		SetActorTickEnabled(false);
	}
	
	Super::Tick(DeltaTime);
}


