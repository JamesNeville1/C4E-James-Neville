#include "TargetComponent.h"
 
#include "GameRule_Target.h"
#include "HealthComponent.h"
 
UTargetComponent::UTargetComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	_PointsValue = 1;
}
 
void UTargetComponent::BeginPlay()
{
	Super::BeginPlay();
 
	AActor* owner = GetOwner();
	_Health = owner->FindComponentByClass<UHealthComponent>();
	if(_Health == nullptr)
	{
		_Health = NewObject<UHealthComponent>(owner, TEXT("Health"));
		owner->AddInstanceComponent(_Health);
		_Health->RegisterComponent();
		owner->Modify();
	}
 
	_Health->OnDead.AddUniqueDynamic(this, &UTargetComponent::Handle_HealthDead);
	//this event doesnt exist until you make the GameRule_Target class so make a todo and come back here after
	UGameRule_Target::OnRequestTargets.AddUniqueDynamic(this, &UTargetComponent::Handle_GameRuleRequestTargets);
 
	OnTargetRegistered.Broadcast(this);
}
 
void UTargetComponent::Handle_GameRuleRequestTargets()
{
	OnTargetRegistered.Broadcast(this);
}
 
void UTargetComponent::Handle_HealthDead(AController* causer)
{
	OnDestroyed.Broadcast(this, causer, _PointsValue);
	GetOwner()->Destroy();
}