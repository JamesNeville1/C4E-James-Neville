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
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGuyDeathSignature);

UCLASS(Abstract)
class C4E_NEVILLE_API AP_Guy : public ACharacter, public  IGuyInputable, public IGuyReturns
{
	GENERATED_BODY()

public:
	AP_Guy();
	
	virtual void BeginPlay() override;
	void LateBeginPlay(bool played);
	
	virtual void Input_Look_Implementation(FVector2D value) override;
	virtual void Input_Move_Implementation(FVector2D value) override;
	virtual void Input_JumpPressed_Implementation() override;
	virtual void Input_JumpReleased_Implementation() override;
	virtual void Input_SpecialPressed_Implementation() override;
	virtual void Input_CharacterSwapPressed_Implementation() override;
	
	virtual UInputMappingContext* GetMappingContext_Implementation() override;

	virtual AP_Guy* Return_Self_Implementation() override;
	
	FSwapGuySignature OnSwapGuy;
	FOnGuyDeathSignature OnGuyDeath;
	
	void OnSwapGuyInit(APC_Guy* controller);
	
protected:
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	//TObjectPtr<UCameraComponent> _Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> _Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UHealthComponent> _Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInputMappingContext> _InputMapping;

	FHitResult SpecialLineTraceLogic(FName profile, float range);
	
	UFUNCTION()
	virtual void SpecialLogic() {};
private:
	UFUNCTION()
	void Handle_HealthComponentDead(AController* causer);
	UFUNCTION()
	void Handle_HealthComponentDamaged(float newHealth, float maxHealth, float change);
	UFUNCTION(BlueprintCallable)
	void Handle_OnOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};