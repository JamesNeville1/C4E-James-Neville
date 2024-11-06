#include "CandyComponent.h"

#include "../GameMode/GR_Candy.h"
#include "C4E_Neville/Interface/GameRuleReturns.h"
#include "GameFramework/GameMode.h"
#include "Kismet/GameplayStatics.h"

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
	IGameRuleReturns::Execute_GR_Candy_Ref(UGameplayStatics::GetGameMode(GetWorld()))->RegisterCandy(this);
}

void UCandyComponent::Interact_Implementation()
{
	_OnCandyEaten.Broadcast();
	GetOwner()->Destroy();
}
