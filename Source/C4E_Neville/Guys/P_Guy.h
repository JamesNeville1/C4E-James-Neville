#pragma once

#include "CoreMinimal.h"
#include "C4E_Neville/Controller/GuyInputable.h"
#include "GameFramework/Character.h"
#include "P_Guy.generated.h"

class UHealthComponent;
class UCameraComponent;
class UCharacterMovementComponent;
class UCapsuleComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSwapGuySignature);

UCLASS(Abstract)
class C4E_NEVILLE_API AP_Guy : public ACharacter, public  IGuyInputable
{
	GENERATED_BODY()

public:
	AP_Guy();
	
	virtual void BeginPlay() override;
	virtual void Input_Look_Implementation(FVector2D value) override;
	virtual void Input_Move_Implementation(FVector2D value) override;
	virtual void Input_JumpPressed_Implementation() override;
	virtual void Input_JumpReleased_Implementation() override;
	virtual void Input_SpecialPressed_Implementation() override;
	virtual void Input_CharacterSwapPressed_Implementation() override;
	
	virtual UInputMappingContext* GetMappingContext_Implementation() override;

	FSwapGuySignature OnSwapGuy;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> _Camera;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UHealthComponent> _Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInputMappingContext> _InputMapping;

	UFUNCTION()
	virtual void SpecialLogic() {};
private:
	UFUNCTION()
	void Handle_HealthComponentDead(AController* causer);
	UFUNCTION()
	void Handle_HealthComponentDamaged(float newHealth, float maxHealth, float change);
};