#include "P_Guy_Lil.h"

#include "P_Guy_Big.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void AP_Guy_Lil::SpecialLogic()
{
	FVector start = _Camera->GetComponentLocation();

	FVector	end = UKismetMathLibrary::GetForwardVector(_Camera->GetComponentRotation());
	end *= _SpecialRange;
	end += start;


	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Add(this);
	FHitResult hitResult;

	UKismetSystemLibrary::LineTraceSingleByProfile(
		GetWorld(), start, end, "Pawn",
		false, actorsToIgnore, EDrawDebugTrace::Persistent, hitResult, true);

	bool guard =
		(hitResult.HitObjectHandle == nullptr) ||
		(!UKismetMathLibrary::ClassIsChildOf(hitResult.HitObjectHandle.FetchActor()->GetClass(), AP_Guy_Big::StaticClass()));
	if (guard) return;
	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, hitResult.HitObjectHandle.FetchActor()->StaticClass()->GetName());
	AlertBigGuyOfSpecial.Broadcast();
}