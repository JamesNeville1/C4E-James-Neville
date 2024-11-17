#pragma once

#include "CoreMinimal.h"
#include "C4E_Neville/Interface/GuyInputable.h"
#include "GameFramework/Character.h"
#include "Pumpkin.generated.h"

UCLASS()
class C4E_NEVILLE_API APumpkin : public ACharacter, public IGuyInputable
{
	GENERATED_BODY()

public:
	APumpkin();

protected:
	virtual void BeginPlay() override;
	
	virtual void Input_Look_Implementation(FVector2D value) override;
	virtual void Input_Move_Implementation(FVector2D value) override;
	virtual void Input_JumpPressed_Implementation() override;
	virtual void Input_JumpReleased_Implementation() override;
	virtual UBehaviorTree* GetBehaviorTree_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UBehaviorTree> _BehaviorTree;
};
