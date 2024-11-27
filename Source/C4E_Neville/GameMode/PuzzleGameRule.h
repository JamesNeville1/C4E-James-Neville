#pragma once

#include "CoreMinimal.h"
#include "C4E_Neville/Interface/PuzzleGameRuleCheck.h"
#include "Components/ActorComponent.h"
#include "PuzzleGameRule.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPuzzleGameRuleCompleteSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class C4E_NEVILLE_API UPuzzleGameRule : public UActorComponent, public IPuzzleGameRuleLogic
{
	GENERATED_BODY()

public:
	UPuzzleGameRule();

	FPuzzleGameRuleCompleteSignature OnPuzzleGameRuleComplete;

	bool _IsRequiredToCompleteGame = false;

	virtual bool IsObjectiveGameRule_Implementation() override;

protected:
	void BroadcastGameRuleComplete();
};
