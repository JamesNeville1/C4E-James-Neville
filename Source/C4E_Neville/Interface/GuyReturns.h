#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GuyReturns.generated.h"

class AP_Guy;

UINTERFACE()
class UGuyReturns : public UInterface
{
	GENERATED_BODY()
};

class C4E_NEVILLE_API IGuyReturns
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	AP_Guy* Return_Self();
	
};
