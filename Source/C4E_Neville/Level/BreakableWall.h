#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BreakableWall.generated.h"

class UBoxComponent;
class UHealthComponent;

UCLASS()
class C4E_NEVILLE_API ABreakableWall : public AActor
{
	GENERATED_BODY()

public:
	ABreakableWall();

protected:
	virtual void BeginPlay() override;

	TObjectPtr<UHealthComponent> _Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UBoxComponent> _Collider;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> _Mesh;

	UFUNCTION(BlueprintNativeEvent, DisplayName = "On Death")
	void RecieveOnDeath();

private:
	UFUNCTION()
	void Handle_OnDeath(AController* causer);
};
