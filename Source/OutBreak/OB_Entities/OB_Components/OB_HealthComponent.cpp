﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "OB_HealthComponent.h"

UOB_HealthComponent::UOB_HealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UOB_HealthComponent::AddHealth(const float Amount)
{
	const float NewHealth = CurrentHealth + Amount;
	SetHealth(NewHealth);
}

void UOB_HealthComponent::RemoveHealth(const float Amount)
{
	const float NewHealth = CurrentHealth - Amount;
	SetHealth(NewHealth);
}


void UOB_HealthComponent::SetHealth(const float NewHealth)
{
	const float SupposedHealth = FMath::Clamp(NewHealth, 0.f, MaxHealth);
	
	if (SupposedHealth <= 0.f)
	{
		OnDeath.Broadcast();
		return;
	}

	CurrentHealth = SupposedHealth;
	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth, GetHealthRatio());
}

void UOB_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHealth(MaxHealth);
}
