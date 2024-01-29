// Fill out your copyright notice in the Description page of Project Settings.


#include "OB_ManualWeapon.h"

#include "OutBreak/OB_Character/OB_Character.h"
#include "OutBreak/OB_Items/OB_Weapons/OB_AmmoComponent.h"
#include "OutBreak/OB_Items/OB_Weapons/OB_Projectile.h"


AOB_ManualWeapon::AOB_ManualWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AOB_ManualWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AOB_ManualWeapon::Fire()
{
	Super::Fire();

	Shoot();
}

void AOB_ManualWeapon::StopFire()
{
	Super::StopFire();
}

void AOB_ManualWeapon::Shoot()
{
	Super::Shoot();

	const APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
	const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
	const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(ProjectileSpawnOffset);
	
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
	GetWorld()->SpawnActor<AOB_Projectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);

	AmmoComponent->Shoot();

	PlayFireAnimations();
}


