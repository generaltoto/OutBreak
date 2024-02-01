// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OB_HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnHealthChanged, float, CurrentHealth, float, MaxHealth, float, HealthRatio);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class OUTBREAK_API UOB_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UOB_HealthComponent();

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthRatio() const { return CurrentHealth / MaxHealth; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetCurrentHealth() const { return CurrentHealth; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetMaxHealth() const { return MaxHealth; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	void AddHealth(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Health")
	void RemoveHealth(float Amount);

	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsDead() const { return CurrentHealth <= 0.f; }

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnDeath OnDeath;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetHealth(float NewHealth);
	
	virtual void BeginPlay() override;

private:
	// Prevents OnDeath from being broadcasted multiple times
	bool bIsDeathHandled;
};
