#include "P_Guy_Big.h"

AP_Guy_Big::AP_Guy_Big()
{
	_LilGuyAttachPoint = CreateDefaultSubobject<UChildActorComponent>(TEXT("Lil Guy Attach Point"));
	_LilGuyAttachPoint->SetupAttachment(RootComponent);
}

void AP_Guy_Big::SpecialLogic()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("Stetchhhhhhh :)"));
}
