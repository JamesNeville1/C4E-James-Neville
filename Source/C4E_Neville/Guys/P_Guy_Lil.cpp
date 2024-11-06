#include "P_Guy_Lil.h"

#include "P_Guy_Big.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void AP_Guy_Lil::SpecialLogic()
{
	FHitResult hitResult = SpecialLineTraceLogic("Pawn", _SpecialRange);

	bool guard =
		(hitResult.HitObjectHandle == nullptr) ||
		(!UKismetMathLibrary::ClassIsChildOf(hitResult.HitObjectHandle.FetchActor()->GetClass(), AP_Guy_Big::StaticClass()));

	FString test = hitResult.HitObjectHandle == nullptr ? "t" : "f";
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, test);
	
	if (guard) return;
	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, hitResult.HitObjectHandle.FetchActor()->StaticClass()->GetName());
	AlertBigGuyOfSpecial.Broadcast();
}