#pragma once

#include "CoreMinimal.h"
#include "GameRule.h"
#include "GameRule_Target.generated.h"

class UTargetComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGRTargetRequestTargetsSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class C4E_NEVILLE_API UGameRule_Target : public UGameRule
{
	GENERATED_BODY()

public:
	UGameRule_Target();

	static inline FGRTargetRequestTargetsSignature OnRequestTargets;

	virtual void Init() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UTargetComponent>> _Targets;

	int _AmountRemaining;

private:
	UFUNCTION()
	void Handle_TargetRegistered(UTargetComponent* target);
	UFUNCTION()
	void Handle_TargetDestroyed(UTargetComponent* target, AController* causer, int targetValue);
};
