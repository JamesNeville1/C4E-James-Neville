#pragma once

#include "CoreMinimal.h"
#include "C4E_Neville/Guys/P_Guy.h"
#include "GameFramework/GameMode.h"
#include "GM_Puzzle.generated.h"


class APC_Guy;
class AP_Guy;

UCLASS(Abstract)
class C4E_NEVILLE_API AGM_Puzzle : public AGameMode
{
	GENERATED_BODY()

public:
	AGM_Puzzle();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<AP_Guy*, AP_Guy*> _SwapList;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<TSubclassOf<AP_Guy>, TSubclassOf<AP_Guy>> _SwapListOrder;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APC_Guy* _ControllerRef;
	
	UFUNCTION()
	void SwapCharacter();
	
	virtual void BeginPlay() override;
};
