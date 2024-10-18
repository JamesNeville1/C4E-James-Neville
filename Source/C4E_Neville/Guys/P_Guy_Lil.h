// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "P_Guy.h"
#include "P_Guy_Lil.generated.h"

UCLASS(Abstract)
class C4E_NEVILLE_API AP_Guy_Lil : public AP_Guy
{
	GENERATED_BODY()

public:
	virtual void SpecialLogic() override;
};
