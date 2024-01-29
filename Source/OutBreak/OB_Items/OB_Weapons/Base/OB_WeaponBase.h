// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OB_WeaponBase.generated.h"

UCLASS()
class OUTBREAK_API AOB_WeaponBase : public AActor
{
	GENERATED_BODY()

public:
	AOB_WeaponBase();

	virtual void Tick(float DeltaTime) override;

	FName& GetName() { return WeaponName; }

protected:
	virtual void BeginPlay() override;

	/** Weapon Stats */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Stats)
	FName WeaponName;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category=Stats)
	TObjectPtr<class UOB_AmmoComponent> AmmoComponent;
	
	/** Components */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Components)
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Components)
	class UBoxComponent* PickupTrigger;

	/** Projectile */

	UPROPERTY(EditDefaultsOnly, Category=Fire)
	TSubclassOf<class AOB_Projectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Fire)
	USoundBase* FireSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Fire)
	UAnimMontage* FireAnimation;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Fire)
	FVector ProjectileSpawnOffset;

	/** Input */

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* FireAction;
	
	UFUNCTION(BlueprintCallable, Category=Input)
	virtual void Fire();

	UFUNCTION(BlueprintCallable, Category=Input)
	virtual void StopFire();
	
	UFUNCTION(BlueprintCallable, Category=Input)
	void TryShoot();

	UFUNCTION(BlueprintCallable, Category=Input)
	virtual void Shoot();

	UFUNCTION(Blueprintable, Category=Input)
	void PlayFireAnimations() const;

	/** Weapon Attachment */

	UFUNCTION(BlueprintCallable, Category=Attachment)
	virtual void TryAttachWeapon(class AOB_Character* TargetCharacter);
	
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintNativeEvent, Category=Attachment)
	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	/** References */

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Refs)
	AOB_Character* Character;
};
