#pragma once

#include "CoreMinimal.h"
#include "PuzzleGameRule.h"
#include "GR_PlayerDeath.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class C4E_NEVILLE_API UGR_PlayerDeath : public UPuzzleGameRule
{
	GENERATED_BODY()

public:
	UGR_PlayerDeath();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int _SharedLives;
public:
	UFUNCTION()
	void AlertPlayerDeath();
};
