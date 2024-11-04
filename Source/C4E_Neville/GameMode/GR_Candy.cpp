#include "GR_Candy.h"

#include "CandyComponent.h"
#include "C4E_Neville/Interface/CandyReturns.h"
#include "C4E_Neville/Level/Candy.h"
#include "Kismet/GameplayStatics.h"

UGR_Candy::UGR_Candy()
{
}

void UGR_Candy::BeginPlay()
{
	RegisterCandies();
	Super::BeginPlay();
}

void UGR_Candy::RegisterCandies() //ToDo: Spawn on play
{
	TArray<UCandyComponent*> candyComponents;

	
	TArray<AActor*> actorsInWorld;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(),actorsInWorld);
	for (AActor* actor : actorsInWorld)
	{
		  TSet<UActorComponent*> compList = actor->GetComponents();
		  for (UActorComponent* comp : compList)
		  {
		  	UCandyComponent* candyComponent = ICandyReturns::Execute_Return_Self(comp);
			if(IsValid(candyComponent))
			{
				
				candyComponents.Add(candyComponent);
			}
		  }
	}

	for (UCandyComponent* candy : candyComponents)
	{
		candy->_OnCandyEaten.AddUniqueDynamic(this, &UGR_Candy::CandyEatenAlert);;
	}
	//_Instance->CandyEatenAlert();
}

void UGR_Candy::CandyEatenAlert()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("Candy Eaten"));
	//_CurrentCandy -= 1;

	//int test = 0;
	//test += _CurrentCandy;

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT(test));
	//if(test <= 0)
	//{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT(":o"));
	//}
}
