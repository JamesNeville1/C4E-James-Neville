#include "P_Guy_Lil.h"

#include "P_Guy_Big.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Physics/ImmediatePhysics/ImmediatePhysicsShared/ImmediatePhysicsCore.h"

void AP_Guy_Lil::SpecialLogic()
{
}

void AP_Guy_Lil::PickupAlert_Implementation(AP_Guy_Big* bigGuyRef)
{
	FVector goTo = bigGuyRef->_LilGuyAttachPoint->GetComponentLocation();
	FHitResult* test = new FHitResult(); //ToDo: Delete
	GetCharacterMovement()->bRunPhysicsWithNoController = false;
	SetActorLocation(goTo, false, test);
	SetActorRotation(bigGuyRef->GetCapsuleComponent()->GetComponentRotation());
	AttachToActor(bigGuyRef, FAttachmentTransformRules::KeepWorldTransform);
}

void AP_Guy_Lil::ThrowAlert_Implementation(AP_Guy_Big* bigGuyRef, float throwSpeed)
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	GetCharacterMovement()->bRunPhysicsWithNoController = true;
	FVector dir = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetActorForwardVector();
	LaunchCharacter(dir * throwSpeed, false, false);
}
