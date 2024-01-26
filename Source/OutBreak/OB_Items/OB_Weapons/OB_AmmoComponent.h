// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OB_AmmoComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAmmoChanged, int32, CurrentAmmo, int32, AmmoInReserve);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class OUTBREAK_API UOB_AmmoComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UOB_AmmoComponent();

	bool CanShoot() const { return CurrentAmmo > 0; }

	/** Reload */

	UFUNCTION(BlueprintCallable, Category=Shoot)
	void Shoot();

	UFUNCTION(BlueprintCallable, Category=Reload)
	void Reload();
	
	UPROPERTY(BlueprintAssignable, Category=Events)
	FOnAmmoChanged OnAmmoChanged;

	/** Getters */

	UFUNCTION(BlueprintCallable, Category=Ammo)
	int32 GetCurrentAmmo() const { return CurrentAmmo; }

	UFUNCTION(BlueprintCallable, Category=Ammo)
	int32 GetAmmoInReserve() const { return AmmoInReserve; }

protected:
	virtual void BeginPlay() override;

	/** Reload */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Reload)
	USoundBase* ReloadSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Reload)
	UAnimMontage* ReloadAnimation;
	
	/** Ammo */

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 CurrentAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo", meta = (ClampMin = 0, ClampMax = 100))
	int32 AmmoPerClip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo", meta = (ClampMin = 0, ClampMax = 1000))
	int32 AmmoInReserve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo", meta = (ClampMin = 0, ClampMax = 1000))
	int32 MaxReserveAmmo;
};
