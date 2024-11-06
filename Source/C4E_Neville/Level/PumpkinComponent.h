#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PumpkinComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPumpkinDefeatSignature);

class UHealthComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class C4E_NEVILLE_API UPumpkinComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPumpkinComponent();

	FOnPumpkinDefeatSignature _OnPumpkinDefeat;

protected:
	virtual void BeginPlay() override;

	TObjectPtr<UHealthComponent> _Health;
private:
	UFUNCTION()
	void Handle_HealthDead(AController* causer);
	void LateBeginPlay(bool played);
public:
};
