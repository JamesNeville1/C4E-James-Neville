#pragma once

#include "CoreMinimal.h"
#include "C4E_Neville/Interface/GuyInputable.h"
#include "C4E_Neville/Interface/PumpkinInputable.h"
#include "GameFramework/Character.h"
#include "Pumpkin.generated.h"

UCLASS()
class C4E_NEVILLE_API APumpkin : public ACharacter, public IPumpkinInputable
{
	GENERATED_BODY()

public:
	APumpkin();

	FTimerHandle _CheckDistTimerHandle;
	FTimerDelegate _CheckDistTimerDel;

	void AISetup();

protected:
	virtual void BeginPlay() override;
	
	virtual UBehaviorTree* GetBehaviorTree_Implementation() override;
	virtual FVector GetNextPatrolPoint_Implementation() override;
	virtual FVector GetCurrentPatrolPoint_Implementation() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<AActor*> _PatrolPoints;
	int _PatrolPointIndex;	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UBehaviorTree> _BehaviorTree;
};
