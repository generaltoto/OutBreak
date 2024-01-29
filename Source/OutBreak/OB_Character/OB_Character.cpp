// Copyright Epic Games, Inc. All Rights Reserved.

#include "OB_Character.h"
#include "OutBreak/OB_Items/OB_Weapons/OB_Projectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "OutBreak/OB_Entities/OB_Components/OB_HealthComponent.h"
#include "OutBreak/OB_Items/OB_Weapons/OB_WeaponBase.h"

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
