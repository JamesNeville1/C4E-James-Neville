#pragma once

#include "CoreMinimal.h"
#include "C4E_Neville/Interface/GuyInputable.h"
#include "C4E_Neville/Interface/GuyReturns.h"
#include "GameFramework/Character.h"
#include "P_Guy.generated.h"

class UHealthComponent;
class UCameraComponent;
class UCharacterMovementComponent;
class UCapsuleComponent;
class APC_Guy;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSwapGuySignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSpecialLogicSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGuyRespawnCheckAlertSignature, AP_Guy*, guy);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGuyDamageUIAlertSignature, float, normalisedHealth, FLinearColor, colour);

UCLASS(Abstract)
class C4E_NEVILLE_API AP_Guy : public ACharacter, public  IGuyInputable, public IGuyReturns
{
	GENERATED_BODY()

public:
	AP_Guy();
	
	virtual void Input_Look_Implementation(FVector2D value) override;
	virtual void Input_Move_Implementation(FVector2D value) override;
	virtual void Input_MovePressed_Implementation() override;
	virtual void Input_MoveReleased_Implementation() override;
	virtual void Input_JumpPressed_Implementation() override;
	virtual void Input_JumpReleased_Implementation() override;
	virtual void Input_SpecialPressed_Implementation() override;
	virtual void Input_CharacterSwapPressed_Implementation() override;
	virtual void UnPossessed() override;
	
	virtual UInputMappingContext* GetMappingContext_Implementation() override;

	virtual AP_Guy* Return_Self_Implementation() override;
	
	FSwapGuySignature OnSwapGuy;
	FOnGuyRespawnCheckAlertSignature OnRespawnAlertCheck;
	FOnGuyDamageUIAlertSignature OnDamageUIAlert;

	virtual void GuySetup(APC_Guy* controller);

	UFUNCTION()
	void EyeBallFramesStart();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UHealthComponent> _Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor _HealthColour;
protected:
	FSpecialLogicSignature OnSpecialLogic;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase* _FootstepSFX;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float _TimeBetweenSteps;
	FTimerHandle _FootstepTimer;
	void PlayFootStep();
	
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	//TObjectPtr<UCameraComponent> _Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> _Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInputMappingContext> _InputMapping;
	
	FHitResult SpecialLineTraceLogic(FName profile, float range);
	
	UFUNCTION()
	virtual void SpecialLogic();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float _EyeBallFrameLength;
	
private:
	UFUNCTION()
	void Handle_HealthComponentDead(AController* causer);
	UFUNCTION()
	void Handle_HealthComponentDamaged(float newHealth, float maxHealth, float change);
	UFUNCTION(BlueprintCallable)
	void Handle_OnOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	FTimerHandle _EyeBallTimerHandle;

	void EyeBallFramesStop();
};