#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Candy.generated.h"

class USphereComponent;

UCLASS()
class C4E_NEVILLE_API ACandy : public AActor
{
	GENERATED_BODY()

public:
	ACandy();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USphereComponent> _Collider;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> _Mesh;
	
private:
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
