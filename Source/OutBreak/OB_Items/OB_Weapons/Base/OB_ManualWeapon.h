// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OB_WeaponBase.h"
#include "OB_ManualWeapon.generated.h"

UCLASS()
class OUTBREAK_API AOB_ManualWeapon : public AOB_WeaponBase
{
	GENERATED_BODY()

public:
	AOB_ManualWeapon();

protected:
	virtual void BeginPlay() override;

	virtual void Fire() override;
	
	virtual void StopFire() override;

	virtual void Shoot() override;
};
