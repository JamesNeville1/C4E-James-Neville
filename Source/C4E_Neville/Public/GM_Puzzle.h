#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GM_Puzzle.generated.h"


class AP_Guy;

UCLASS()
class C4E_NEVILLE_API AGM_Puzzle : public AGameMode
{
	GENERATED_BODY()

public:
	AGM_Puzzle();
	
	//virtual AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName) override;
	//TArray<TObjectPtr<AActor>> _PlayerStarts;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<AActor*> SwapList;
	
	void SwapCharacter();

	
};
