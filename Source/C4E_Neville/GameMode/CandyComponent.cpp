#include "CandyComponent.h"

#include "GR_Candy.h"
#include "C4E_Neville/Interface/InfoReturns.h"
#include "C4E_Neville/Static Data/GI_Info.h"

UCandyComponent::UCandyComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCandyComponent::BeginPlay()
{
	GetWorld()->GetOnBeginPlayEvent().AddUObject(this, &UCandyComponent::LateBeginPlay);
	Super::BeginPlay();
}

void UCandyComponent::LateBeginPlay(bool played)
{
	IInfoReturns::Execute_ReturnInstance(GetWorld()->GetGameInstance())->_CandyGR->RegisterCandy(this); //ToDo: Consider making reference to gamemode with interface of every gamerule (can be null)
}

void UCandyComponent::Interact_Implementation()
{
	_OnCandyEaten.Broadcast();
	GetOwner()->Destroy();
}
