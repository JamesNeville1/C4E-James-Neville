#include "P_Guy_Strong.h"

#include "C4E_Neville/Level/PumpkinComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void AP_Guy_Strong::SpecialLogic()
{

	FHitResult hitResult = SpecialLineTraceLogic("WorldDynamic", _SpecialRange);
	
	bool guard =
		(hitResult.GetActor() == nullptr) ||
		(hitResult.GetActor()->GetComponentByClass(UPumpkinComponent::StaticClass()) == nullptr);


	//FString test = hitResult.GetActor()->GetComponentByClass(UPumpkinComponent::StaticClass()) == nullptr ? "T" : "F";
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, test);
	
	if (guard) return;

	UGameplayStatics::ApplyDamage(hitResult.GetActor(), 1, GetController(), this, UDamageType::StaticClass());
	
	//Super::SpecialLogic();
}
