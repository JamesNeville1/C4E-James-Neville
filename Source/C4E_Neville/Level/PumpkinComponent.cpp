#include "PumpkinComponent.h"

#include "C4E_Neville/ClassStuff/HealthComponent.h"
#include "C4E_Neville/GameMode/GR_Pumpkin.h"
#include "C4E_Neville/Interface/GameRuleReturns.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameMode.h"


UPumpkinComponent::UPumpkinComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPumpkinComponent::BeginPlay()
{
	AActor* owner = GetOwner();

	_Health = owner->FindComponentByClass<UHealthComponent>();

	if (_Health == nullptr)
	{
		//Create
		_Health = NewObject<UHealthComponent>(owner, TEXT("Health"));
		owner->AddInstanceComponent(_Health);

		//Register
		_Health->RegisterComponent();
		owner->Modify();
	}

	_Health->OnDead.AddUniqueDynamic(this, &UPumpkinComponent::Handle_HealthDead);

	if (_Tracked)
	{
		//GetWorld()->GetOnBeginPlayEvent().AddUObject(this, &UPumpkinComponent::LateBeginPlay);
		IGameRuleReturns::Execute_GR_Pumpkin_Ref(UGameplayStatics::GetGameMode(GetWorld()))->RegisterPumpkin(this);
	}

	Super::BeginPlay();
}

void UPumpkinComponent::Handle_HealthDead(AController* causer)
{
	_OnPumpkinDefeat.Broadcast();
	GetOwner()->Destroy();
}
