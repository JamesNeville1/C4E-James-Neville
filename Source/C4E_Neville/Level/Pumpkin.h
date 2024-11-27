#pragma once

#include "CoreMinimal.h"
#include "C4E_Neville/Interface/GuyInputable.h"
#include "C4E_Neville/Interface/PumpkinInputable.h"
#include "GameFramework/Character.h"
#include "Pumpkin.generated.h"

class UAISenseConfig_Sight;
class UAIPerceptionComponent;

UCLASS()
class C4E_NEVILLE_API APumpkin : public ACharacter, public IPumpkinInputable
{
	GENERATED_BODY()

public:
	APumpkin();

	void AISetup();

protected:
	virtual void BeginPlay() override;

	virtual UBehaviorTree* GetBehaviorTree_Implementation() override;
	virtual void Input_Attack_Implementation(AActor* target) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UBehaviorTree> _BehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UChildActorComponent> _AttackPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _AttackCapsuleHalfHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _AttackRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int _Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TEnumAsByte<EObjectTypeQuery>> _ObjectTypeToHit;
};
