#include "GameRule_Target.h"
 
#include "TargetComponent.h"
 
UGameRule_Target::UGameRule_Target()
{
	PrimaryComponentTick.bCanEverTick = false;
}
 
void UGameRule_Target::Init()
{
	Super::Init();
	UTargetComponent::OnTargetRegistered.AddUniqueDynamic(this, &UGameRule_Target::Handle_TargetRegistered);
	OnRequestTargets.Broadcast();
}
 
void UGameRule_Target::Handle_TargetRegistered(UTargetComponent* target)
{
	if(_Targets.Contains(target)) { return; }
	_Targets.Add(target);
	target->OnDestroyed.AddUniqueDynamic(this, &UGameRule_Target::Handle_TargetDestroyed);
	_AmountRemaining++;
}
 
void UGameRule_Target::Handle_TargetDestroyed(UTargetComponent* target, AController* causer, int targetValue)
{
	_Targets.Remove(target);
	_AmountRemaining--;
	BroadcastPointsScored(causer, targetValue);
 
	if(_AmountRemaining == 0)
	{
		BroadcastComplete();
	}
}