#include "BTS_GetDistanceToActor.h"
 
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"

UBTS_GetDistanceToActor::UBTS_GetDistanceToActor()
{
	bNotifyTick = true;
	bNotifyBecomeRelevant = false;
	bNotifyCeaseRelevant = false;
 
	Key_Pos.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTS_GetDistanceToActor, Key_Pos));
	Key_Self.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTS_GetDistanceToActor, Key_Self), AActor::StaticClass());
	Key_DistanceAllowance.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UBTS_GetDistanceToActor, Key_DistanceAllowance));
}
 
void UBTS_GetDistanceToActor::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
 
	UBlackboardData* BBAsset = GetBlackboardAsset();
	if(ensure(BBAsset))
	{
		Key_Pos.ResolveSelectedKey(*BBAsset);
		Key_Self.ResolveSelectedKey(*BBAsset);
		Key_DistanceAllowance.ResolveSelectedKey(*BBAsset);
	}
}
 
void UBTS_GetDistanceToActor::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	float DeltaSeconds)
{
	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();

	float distance = UKismetMathLibrary::Vector_Distance
		(Cast<AActor>(BBComp->GetValueAsObject(Key_Self.SelectedKeyName))->GetActorLocation(),
		BBComp->GetValueAsVector(Key_Pos.SelectedKeyName));

	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, "AAAAAAAAAAA");
	
	if(distance <= BBComp->GetValueAsFloat(Key_DistanceAllowance.SelectedKeyName))
	{
		//BBComp->SetValueAsBool("ReachedPatrolPoint", true);
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}