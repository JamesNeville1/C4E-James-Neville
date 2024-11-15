#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PuzzleGameRule.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPuzzleGameRuleCompleteSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class C4E_NEVILLE_API UPuzzleGameRule : public UActorComponent
{
	GENERATED_BODY()

public:
	UPuzzleGameRule();

	FPuzzleGameRuleCompleteSignature OnPuzzleGameRuleComplete;

	bool _IsRequiredToCompleteGame = false; 

protected:
	void BroadcastGameRuleComplete();
};
