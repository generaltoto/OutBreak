// Fill out your copyright notice in the Description page of Project Settings.


#include "OB_WeaponBase.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "OB_AmmoComponent.h"
#include "OB_Projectile.h"
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
	if (Character == nullptr || Character->GetController() == nullptr) return;

	TryShoot();
}

void AOB_WeaponBase::TryShoot()
{
	UWorld* World = GetWorld();
	if (ProjectileClass == nullptr || World == nullptr) return;

	// Check if the player is able to shoot
	if (!AmmoComponent->CanShoot())
	{
		AmmoComponent->Reload();
		return;
	}

	const APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
	const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
	const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(ProjectileSpawnOffset);
	
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
	World->SpawnActor<AOB_Projectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);

	AmmoComponent->Shoot();

	PlayFireAnimations();
}

void AOB_WeaponBase::PlayFireAnimations()
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
	TryAttachWeapon(Cast<AOB_Character>(OtherActor));
}

