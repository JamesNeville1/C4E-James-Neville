#include "BTS_GetDistanceFromActor.h"
 
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"

UBTS_GetDistanceFromActor::UBTS_GetDistanceFromActor()
{
	bNotifyTick = true;
	bNotifyBecomeRelevant = false;
	bNotifyCeaseRelevant = false;
 
	Key_Target.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTS_GetDistanceFromActor, Key_Target), AActor::StaticClass());
	Key_Self.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTS_GetDistanceFromActor, Key_Self), AActor::StaticClass());
	Key_DistanceOutput.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UBTS_GetDistanceFromActor, Key_DistanceOutput));
}
 
void UBTS_GetDistanceFromActor::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
 
	UBlackboardData* BBAsset = GetBlackboardAsset();
	if(ensure(BBAsset))
	{
		Key_Target.ResolveSelectedKey(*BBAsset);
		Key_Self.ResolveSelectedKey(*BBAsset);
		Key_DistanceOutput.ResolveSelectedKey(*BBAsset);
	}
}
 
void UBTS_GetDistanceFromActor::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	float DeltaSeconds)
{
	UBlackboardComponent* bbComp = OwnerComp.GetBlackboardComponent();

	FVector a = (Cast<AActor>(bbComp->GetValueAsObject(Key_Self.SelectedKeyName))->GetActorLocation());
	a.Z = 0;
	FVector b = Cast<AActor>(bbComp->GetValueAsObject(Key_Target.SelectedKeyName))->GetActorLocation();
	b.Z = 0;
	
	float distance = UKismetMathLibrary::Vector_Distance(a, b);
	
	bbComp->SetValueAsFloat(Key_DistanceOutput.SelectedKeyName, distance);
	
	//GEngine->AddOnScreenDebugMessage(-1, 10000.0f, FColor::Yellow, FString::SanitizeFloat(distance));
	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}