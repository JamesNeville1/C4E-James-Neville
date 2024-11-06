#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Pumpkin.generated.h"

UCLASS()
class C4E_NEVILLE_API APumpkin : public ACharacter
{
	GENERATED_BODY()

public:
	APumpkin();

protected:
	virtual void BeginPlay() override;
	
};
