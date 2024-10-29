#include "CandyComponent.h"

#include "GR_Candy.h"

UCandyComponent::UCandyComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	
}

void UCandyComponent::BeginPlay()
{
	UGR_Candy::ReigesterCandy();
	
	Super::BeginPlay();
}
