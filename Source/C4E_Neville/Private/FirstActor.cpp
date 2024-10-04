// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstActor.h"

#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"


// Sets default values
AFirstActor::AFirstActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	_Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	RootComponent = _Collider;

	_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_Mesh -> SetupAttachment(_Collider);

	_Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	_Arrow -> SetupAttachment(_Collider);

	//_RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Rotating Movement"));
}

void AFirstActor::Handle_ColliderHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Display, TEXT("Ouch!"));
}

void AFirstActor::BeginPlay()
{
	Super::BeginPlay();
	_Collider->OnComponentHit.AddUniqueDynamic(this, &AFirstActor::Handle_ColliderHit);
}


