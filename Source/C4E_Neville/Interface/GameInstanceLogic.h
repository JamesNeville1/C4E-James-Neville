#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameInstanceLogic.generated.h"

UINTERFACE()
class UGameInstanceLogic : public UInterface
{
	GENERATED_BODY()
};

class C4E_NEVILLE_API IGameInstanceLogic
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FName GetNextLevel();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FName GetCurrentLevel();
};
