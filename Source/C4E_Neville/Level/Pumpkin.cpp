#include "Pumpkin.h"

APumpkin::APumpkin()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APumpkin::BeginPlay()
{
	Super::BeginPlay();
	
}

void APumpkin::Input_Look_Implementation(FVector2D value)
{
	
}

void APumpkin::Input_Move_Implementation(FVector2D value)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, "-_-");

	LaunchCharacter(GetActorUpVector() * 10000, false, false);
}

void APumpkin::Input_JumpPressed_Implementation()
{
	
}

void APumpkin::Input_JumpReleased_Implementation()
{
	
}

UBehaviorTree* APumpkin::GetBehaviorTree_Implementation()
{
	return _BehaviorTree;
}

