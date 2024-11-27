#include "Weapon_Hitscan.h"

#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void AWeapon_Hitscan::Fire()
{
	UWorld* const world = GetWorld();
	if (world == nullptr)
	{
		return;
	}

	FHitResult hit(ForceInit);
	FVector start = _Muzzle->GetComponentLocation();
	FVector end = start + (_Muzzle->GetForwardVector() * 1000);

	TArray<AActor*> ActorsToIgnore;

	if (UKismetSystemLibrary::LineTraceSingle(
		world, start, end,
		UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2), false, ActorsToIgnore,
		EDrawDebugTrace::ForDuration, hit, true,
		FLinearColor::Red, FLinearColor::Green, 5))
	{
		UGameplayStatics::ApplyDamage(hit.GetActor(), _Damage, GetOwner()->GetInstigatorController(), GetOwner(),
		                              UGameplayStatics::StaticClass());

		UE_LOG(LogTemp, Display, TEXT("Hit position: %s"), *hit.ImpactPoint.ToString());
	}

	Super::Fire();
}
