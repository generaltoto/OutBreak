// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OB_AmmoComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class OUTBREAK_API UOB_AmmoComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UOB_AmmoComponent();

	bool CanShoot() const { return CurrentAmmo > 0; }

	UFUNCTION(BlueprintCallable, Category = "Ammo")
	void Reload();

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
