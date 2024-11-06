// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "P_Guy.h"
#include "C4E_Neville/Interface/LilGuyPickupAlert.h"
#include "P_Guy_Lil.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAlertBigGuyOfSpecialSignature);

UCLASS(Abstract)
class C4E_NEVILLE_API AP_Guy_Lil : public AP_Guy, public ILilGuyPickupAlert
{
	GENERATED_BODY()

public:
	virtual void SpecialLogic() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float _SpecialRange;

	virtual void PickupAlert_Implementation(AP_Guy_Big* bigGuyRef) override;
	virtual void ThrowAlert_Implementation(AP_Guy_Big* bigGuyRef, float throwSpeed) override;
};
