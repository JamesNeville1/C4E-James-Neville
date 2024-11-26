#include "Pumpkin.h"

#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

APumpkin::APumpkin()
{
	PrimaryActorTick.bCanEverTick = true;

	_AttackPoint = CreateDefaultSubobject<UChildActorComponent>(TEXT("Attack Point"));
	_AttackPoint->SetupAttachment(RootComponent);
}

void APumpkin::AISetup()
{
	
}

void APumpkin::BeginPlay()
{
	Super::BeginPlay();
}

UBehaviorTree* APumpkin::GetBehaviorTree_Implementation()
{
	return _BehaviorTree;
}

void APumpkin::Input_Attack_Implementation(AActor* target)
{
	TArray<FHitResult> hits;
	TArray<AActor*> ignore;

	UKismetSystemLibrary::SphereTraceMultiForObjects(
		GetWorld(), _AttackPoint->GetComponentLocation(), _AttackPoint->GetComponentLocation(), _AttackRadius,
		_ObjectTypeToHit, false, ignore, EDrawDebugTrace::Persistent, hits, true
	);

	for (auto hit : hits)
	{
		if(hit.GetActor() == target)
		{
			UGameplayStatics::ApplyDamage(hit.GetActor(), _Damage, GetController(), this, nullptr);
		}
		else
		{
		}
	}
}

