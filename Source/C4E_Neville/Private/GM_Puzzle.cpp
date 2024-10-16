#include "GM_Puzzle.h"

#include "P_Guy.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"


AGM_Puzzle::AGM_Puzzle()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("TEST"));

	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AP_Guy::StaticClass(), SwapList);
}

void AGM_Puzzle::SwapCharacter()
{
	for (AActor* guy : SwapList)
	{
		AP_Guy* castedGuy = Cast<AP_Guy>(guy);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, castedGuy->Controller.GetName());
		if(castedGuy->Controller != nullptr)
		{
			break;
		}
	}
}
