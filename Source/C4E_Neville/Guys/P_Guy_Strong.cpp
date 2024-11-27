#include "P_Guy_Strong.h"

#include "C4E_Neville/Level/PumpkinComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void AP_Guy_Strong::SpecialLogic()
{

	FHitResult hitResult = LineTraceLogic("WorldDynamic", _SpecialRange);
	
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "test");
	
	bool guard =
		(hitResult.GetActor() == nullptr);

	
	if (guard) return;

	UGameplayStatics::ApplyDamage(hitResult.GetActor(), 1, GetController(), this, UDamageType::StaticClass());
}
