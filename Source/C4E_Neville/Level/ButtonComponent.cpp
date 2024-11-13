#include "ButtonComponent.h"

#include "C4E_Neville/Interface/I_LevelPiece.h"


UButtonComponent::UButtonComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UButtonComponent::Press()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Press"));
	for (AActor* levelPiece : _LevelPieces)
	{
		ILevelPiece::Execute_Trigger(levelPiece);
	}
}

void UButtonComponent::UnPress()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Unpress"));
	for (AActor* levelPiece : _LevelPieces)
	{
		ILevelPiece::Execute_Reverse(levelPiece);
	}
}
