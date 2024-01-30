// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "OB_Character.generated.h"

class AOB_WeaponBase;
class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponChanged, AOB_WeaponBase*, NewWeapon);

UCLASS(config=Game)
class AOB_Character : public ACharacter
{
	GENERATED_BODY()
public:
	AOB_Character();

protected:
	virtual void BeginPlay();

public:

	/** Weapon */
	
	UPROPERTY(BlueprintAssignable, Category = Weapon)
	FOnWeaponChanged OnWeaponChanged;

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void EquipWeapon(AOB_WeaponBase* Weapon);

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void UnequipWeapon();

	/** Getters */

	UFUNCTION(BlueprintCallable, Category = Camera)
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	UFUNCTION(BlueprintCallable, Category = Weapon)
	AOB_WeaponBase* GetCurrentWeapon() const { return CurrentWeapon; }

protected:
	/** Components */
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** Weapon */

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	AOB_WeaponBase* CurrentWeapon;

	/** Health */

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite, Category = Components)
	class UOB_HealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
	TSubclassOf<UDamageType> CanTakeDamageType;
	
	UFUNCTION()
	virtual void OnDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);
	
	UFUNCTION()
	void HandleDeath();
};

