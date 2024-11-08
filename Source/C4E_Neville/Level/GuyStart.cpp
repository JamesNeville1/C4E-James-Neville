#include "GuyStart.h"

AGuyStart::AGuyStart()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AGuyStart::BeginPlay()
{
	Super::BeginPlay();
	
}

TSubclassOf<AP_Guy> AGuyStart::Return_GuyClass_Implementation()
{
	return _MyGuy;
}
