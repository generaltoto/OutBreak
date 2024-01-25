// Fill out your copyright notice in the Description page of Project Settings.

#include "OB_AmmoComponent.h"

#include "Kismet/GameplayStatics.h"


UOB_AmmoComponent::UOB_AmmoComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UOB_AmmoComponent::Reload()
{
	if (AmmoInReserve <= 0 || CurrentAmmo >= AmmoPerClip) return;

	const float AmmoNeeded = AmmoPerClip - CurrentAmmo;
	if (AmmoNeeded > AmmoInReserve)
	{
		CurrentAmmo += AmmoInReserve;
		AmmoInReserve = 0;
	}
	else
	{
		CurrentAmmo += AmmoNeeded;
		AmmoInReserve -= AmmoNeeded;
	}
	

	if (ReloadSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ReloadSound, GetOwner()->GetActorLocation());
	}
	
	if (ReloadAnimation != nullptr)
	{
		USkeletalMeshComponent* Mesh = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
		UAnimInstance* AnimInstance = Mesh->GetAnimInstance();
		
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(ReloadAnimation, 1.f);
		}
	}
}

void UOB_AmmoComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


