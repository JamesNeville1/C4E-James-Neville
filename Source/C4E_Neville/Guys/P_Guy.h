#pragma once

#include "CoreMinimal.h"
#include "C4E_Neville/Interface/GuyInputable.h"
#include "C4E_Neville/Interface/Launchable.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionTypes.h"
#include "P_Guy.generated.h"

class UHealthComponent;
class UCameraComponent;
class UCharacterMovementComponent;
class UCapsuleComponent;
class APC_Guy;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSwapGuySignature);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGuyRespawnCheckAlertSignature, AP_Guy*, guy);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGuyDamageUIAlertSignature, float, normalisedHealth, FLinearColor,
                                             colour);

UCLASS(Abstract)
class C4E_NEVILLE_API AP_Guy : public ACharacter, public IGuyInputable, public IGenericTeamAgentInterface,
                               public ILaunchable
{
	GENERATED_BODY()

public:
	AP_Guy();

	virtual void Launch_Implementation(FVector velocity) override;

	//AI
	virtual FGenericTeamId GetGenericTeamId() const override;
	FGenericTeamId _TeamID = FGenericTeamId(2);

	//Start Eye Ball Frames
	void EyeBallFramesStart();

	//Setup (Called by Controller)
	void GuySetup(APC_Guy* controller);

	//Health Related
	void ResetHealth();
	float GetNormalizedHealth();

	//UI Related
	FLinearColor GetHealthColor();

protected:
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _MaxLookUp = 55.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _MaxLookDown = -45.0f;

	//Health Color (UI)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor _HealthColor;

	//Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UHealthComponent> _Health;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> _Camera;

	//FootStep Related
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase* _FootstepSFX;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float _TimeBetweenSteps;
	FTimerHandle _FootstepTimer;
	void PlayFootstep();

	//Utility
	FHitResult LineTraceLogic(FName profile, float range);

	//Special Logic
	virtual void SpecialLogic();


	//How long after death is the character invincible?
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float _EyeBallFrameLength;

	//Input
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInputMappingContext> _InputMapping;

	virtual void Input_Look_Implementation(FVector2D value) override;
	virtual void Input_Move_Implementation(FVector2D value) override;
	virtual void Input_MovePressed_Implementation() override;
	virtual void Input_MoveReleased_Implementation() override;
	virtual void Input_JumpPressed_Implementation() override;
	virtual void Input_JumpReleased_Implementation() override;
	virtual void Input_SpecialPressed_Implementation() override;
	virtual void Input_CharacterSwapPressed_Implementation() override;
	virtual UInputMappingContext* GetMappingContext_Implementation() override;

	//Pawn Overrides
	virtual void UnPossessed() override;

	//Designer Hooks
	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Play Footstep")
	void RecievePlayFootstep();

	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Input_Look")
	void RecieveInput_Look(const FVector2D& value);

	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Input_Move")
	void RecieveInput_Move(const FVector2D& value);

	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Input_MovePressed")
	void RecieveInput_MovePressed();

	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Input_MoveReleased")
	void RecieveInput_MoveReleased();

	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Input_JumpPressed")
	void RecieveInput_JumpPressed();

	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Input_JumpReleased")
	void RecieveInput_JumpReleased();

	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Input_SpecialPressed")
	void RecieveInput_SpecialPressed();

	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Input_CharacterSwapPressed")
	void RecieveInput_CharacterSwapPressed();

	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Eye Ball Frames Start")
	void RecieveEyeBallFramesStart();

	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Eye Ball Frames Stop")
	void RecieveEyeBallFramesStop();

private:
	//Private Events - Used to alert controller via AMD
	FOnGuyRespawnCheckAlertSignature OnRespawnAlertCheck;
	FOnGuyDamageUIAlertSignature OnDamageUIAlert;
	FSwapGuySignature OnSwapGuy;

	//Handles
	UFUNCTION()
	void Handle_HealthComponentDead(AController* causer);
	UFUNCTION()
	void Handle_HealthComponentDamaged(float newHealth, float maxHealth, float change);
	UFUNCTION()
	void Handle_OnOverlap(UPrimitiveComponent* OverlappedComponent,
	                      AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                      const FHitResult& SweepResult);

	//Eye Ball Frame Related
	FTimerHandle _EyeBallTimerHandle;
	void EyeBallFramesStop();
};
