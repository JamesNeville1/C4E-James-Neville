#include "P_Guy_Big.h"

#include "P_Guy_Lil.h"
#include "Kismet/KismetMathLibrary.h"

AP_Guy_Big::AP_Guy_Big()
{
	_LilGuyAttachPoint = CreateDefaultSubobject<UChildActorComponent>(TEXT("Lil Guy Attach Point"));
	_LilGuyAttachPoint->SetupAttachment(RootComponent);
}

void AP_Guy_Big::Input_CharacterSwapPressed_Implementation()
{
	if(holdingLilGuy)
	{
		ILilGuyPickupAlert::Execute_ThrowAlert(_LilGuyRef, this, launchSpeed);
		
		holdingLilGuy = false;
	}
	//GEngine->AddOnScreenDebugMessage(-1, 10000.0f, FColor::Yellow, TEXT("A"));
	Super::Input_CharacterSwapPressed_Implementation();
}

void AP_Guy_Big::Input_JumpPressed_Implementation()
{
	if(!holdingLilGuy)
	{
		Super::Input_JumpPressed_Implementation();
	}
}

void AP_Guy_Big::SpecialLogic()
{
	if(holdingLilGuy)
	{
		ILilGuyPickupAlert::Execute_ThrowAlert(_LilGuyRef, this, launchSpeed);
		
		holdingLilGuy = false;
	}
	else
	{
		FHitResult hitResult = LineTraceLogic("WorldDynamic", _SpecialRange);

		bool guard =
			(hitResult.GetActor() == nullptr) ||
			(!UKismetMathLibrary::ClassIsChildOf(hitResult.GetActor()->GetClass(), AP_Guy_Lil::StaticClass()));
		if (guard) return;

		ILilGuyPickupAlert::Execute_PickupAlert(hitResult.GetActor(), this);

		_LilGuyRef = hitResult.GetActor();
		
		holdingLilGuy = true;
	}
}
