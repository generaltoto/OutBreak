// Copyright Epic Games, Inc. All Rights Reserved.

#include "OB_Character.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "OutBreak/OB_Entities/OB_Components/OB_HealthComponent.h"
#include "OutBreak/OB_Items/OB_Weapons/Base/OB_WeaponBase.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AOB_Character::AOB_Character()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	USkeletalMeshComponent* Temp = GetMesh();
	Temp->SetupAttachment(FirstPersonCameraComponent);
	Temp->bCastDynamicShadow = false;
	Temp->CastShadow = false;
	Temp->SetOnlyOwnerSee(true);
	Temp->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	HealthComponent = CreateDefaultSubobject<UOB_HealthComponent>(TEXT("HealthComponent"));

}

void AOB_Character::BeginPlay()
{
	Super::BeginPlay();

	OnTakeAnyDamage.AddDynamic(this, &AOB_Character::OnDamageTaken);
	HealthComponent->OnDeath.AddDynamic(this, &AOB_Character::HandleDeath);
}

void AOB_Character::EquipWeapon(AOB_WeaponBase* Weapon)
{
	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	Weapon->AttachToComponent(GetMesh(), AttachmentRules, FName(TEXT("GripPoint")));

	CurrentWeapon = Weapon;
	OnWeaponChanged.Broadcast(CurrentWeapon);
}

void AOB_Character::UnequipWeapon()
{
	CurrentWeapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	CurrentWeapon = nullptr;
	OnWeaponChanged.Broadcast(CurrentWeapon);
}

void AOB_Character::OnDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (DamageType->IsA(CanTakeDamageType) && HealthComponent->IsDead() == false)
	{
		HealthComponent->RemoveHealth(Damage);
	}
}

void AOB_Character::HandleDeath()
{
	GetCharacterMovement()->StopMovementImmediately();

	SetActorHiddenInGame(true);

	DetachFromControllerPendingDestroy();

	FTimerHandle DeathTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeathTimerHandle, [this]()
	{
		UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), TEXT("RestartLevel"), GetWorld()->GetFirstPlayerController());
	}, 2.0f, false);
}
