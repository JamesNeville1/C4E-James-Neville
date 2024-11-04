#include "CandyComponent.h"

#include "GR_Candy.h"

UCandyComponent::UCandyComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCandyComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCandyComponent::Interact_Implementation()
{
	_OnCandyEaten.Broadcast();
	GetOwner()->Destroy();
}
