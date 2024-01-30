// Fill out your copyright notice in the Description page of Project Settings.


#include "OB_WeaponBase.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "OutBreak/OB_Items/OB_Weapons/OB_AmmoComponent.h"
#include "OutBreak/OB_Items/OB_Weapons/OB_Projectile.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "OutBreak/OB_Character/OB_Character.h"


AOB_WeaponBase::AOB_WeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	WeaponMesh->SetupAttachment(Root);

	PickupTrigger = CreateDefaultSubobject<UBoxComponent>("PickupTrigger");
	PickupTrigger->SetupAttachment(Root);

	AmmoComponent = CreateDefaultSubobject<UOB_AmmoComponent>("AmmoComponent");
	AddOwnedComponent(AmmoComponent);
}

void AOB_WeaponBase::BeginPlay()
{
	Super::BeginPlay();

	PickupTrigger->OnComponentBeginOverlap.AddDynamic(this, &AOB_WeaponBase::OnTriggerBeginOverlap);
}

void AOB_WeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AOB_WeaponBase::Fire()
{
}

void AOB_WeaponBase::StopFire()
{
}

void AOB_WeaponBase::TryShoot()
{
	if (ProjectileClass == nullptr) return;

	// Check if the player is able to shoot
	if (!AmmoComponent->CanShoot())
	{
		AmmoComponent->Reload();
		return;
	}

	Shoot();
}

void AOB_WeaponBase::Shoot()
{

}

void AOB_WeaponBase::PlayFireAnimations() const
{
	if (FireSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
	}
	
	if (FireAnimation != nullptr)
	{
		if (UAnimInstance* AnimInstance = Character->GetMesh()->GetAnimInstance(); AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}

void AOB_WeaponBase::TryAttachWeapon(AOB_Character* TargetCharacter)
{
	Character = TargetCharacter;

	if (Character == nullptr) return;

	// If the player already has a weapon equipped, unequip it
	if (Character->GetCurrentWeapon() != nullptr) Character->UnequipWeapon();
	
	Character->EquipWeapon(this);

	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(FireMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &AOB_WeaponBase::Fire);
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &AOB_WeaponBase::StopFire);
		}
	}
}

void AOB_WeaponBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (Character == nullptr) return;

	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(FireMappingContext);
		}
	}
}

void AOB_WeaponBase::OnTriggerBeginOverlap_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player") == false) return;
	
	TryAttachWeapon(Cast<AOB_Character>(OtherActor));
}

