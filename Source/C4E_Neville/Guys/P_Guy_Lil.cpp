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

	if(hitResult.HitObjectHandle == nullptr) return;

	//if(!UKismetMathLibrary::ClassIsChildOf(hitResult.HitObjectHandle.FetchActor()->StaticClass(), AP_Guy_Big::StaticClass())) return; //Make interface to return type
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, hitResult.HitObjectHandle.FetchActor()->StaticClass()->GetName());	
}
