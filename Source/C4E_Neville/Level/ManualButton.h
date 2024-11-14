#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ManualButton.generated.h"


class UBoxComponent;
class UButtonComponent;

UCLASS()

class C4E_NEVILLE_API AManualButton : public AActor
{
	GENERATED_BODY()

public:
	AManualButton();

	UFUNCTION(BlueprintCallable)
	void Handle_OnOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	TObjectPtr<UButtonComponent> _ButtonComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> _Collider;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> _Mesh;

protected:
	virtual void BeginPlay() override;

private:
	bool _Pressed;
};
