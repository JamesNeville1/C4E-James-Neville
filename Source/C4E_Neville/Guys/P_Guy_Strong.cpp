#include "P_Guy_Strong.h"

#include "C4E_Neville/Level/PumpkinComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void AP_Guy_Strong::SpecialLogic()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Smash >:("));

	FHitResult hitResult = SpecialLineTraceLogic("Pawn", _SpecialRange);
	
	bool guard =
		(hitResult.HitObjectHandle == nullptr) ||
		(hitResult.GetActor()->GetComponentByClass(UPumpkinComponent::StaticClass()));
	if (guard) return;

	UGameplayStatics::ApplyDamage(hitResult.GetActor(), 10, GetController(), this, UDamageType::StaticClass());
	
	//Super::SpecialLogic();
}
