#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FloorButton.generated.h"


class UBoxComponent;
class UButtonComponent;

UCLASS()

class C4E_NEVILLE_API AFloorButton : public AActor
{
	GENERATED_BODY()

public:
	AFloorButton();

	UFUNCTION(BlueprintCallable)
	void Handle_OnOverlap(UPrimitiveComponent* OverlappedComponent,
	                      AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                      const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable)
	void Handle_OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                         UPrimitiveComponent* OtherComp,
	                         int32 OtherBodyIndex);
	TObjectPtr<UButtonComponent> _ButtonComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> _Collider;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> _Mesh;

protected:
	virtual void BeginPlay() override;

private:
	int _UseCount;
};
