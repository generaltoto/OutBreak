// Fill out your copyright notice in the Description page of Project Settings.


#include "OB_AutomaticWeapon.h"

#include "OutBreak/OB_Character/OB_Character.h"
#include "OutBreak/OB_Items/OB_Weapons/OB_AmmoComponent.h"
#include "OutBreak/OB_Items/OB_Weapons/OB_Projectile.h"


AOB_AutomaticWeapon::AOB_AutomaticWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AOB_AutomaticWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AOB_AutomaticWeapon::Fire()
{
	Super::Fire();
	
	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &AOB_AutomaticWeapon::TryShoot, FireRate, true);
}

void AOB_AutomaticWeapon::StopFire()
{
	Super::StopFire();
	
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
}

void AOB_AutomaticWeapon::Shoot()
{
	const APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
	const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
	const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(ProjectileSpawnOffset);
	
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
	GetWorld()->SpawnActor<AOB_Projectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);

	AmmoComponent->Shoot();

	PlayFireAnimations();
}

void AOB_AutomaticWeapon::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorldTimerManager().ClearTimer(FireTimerHandle);
	GetWorldTimerManager().ClearAllTimersForObject(this);
}


