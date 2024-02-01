// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OB_WeaponBase.h"
#include "OB_AutomaticWeapon.generated.h"

UCLASS()
class OUTBREAK_API AOB_AutomaticWeapon : public AOB_WeaponBase
{
	GENERATED_BODY()

public:
	AOB_AutomaticWeapon();

protected:
	virtual void BeginPlay() override;

	virtual void Fire() override;
	
	virtual void StopFire() override;

	virtual void Shoot() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Fire)
	FTimerHandle FireTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Fire, meta=(UIMin = 0.05, UIMax = 10.0))
	float FireRate = 0.1f;
};
