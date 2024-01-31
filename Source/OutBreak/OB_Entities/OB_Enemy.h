// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "OB_EnemyStates.h"
#include "OB_Enemy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnStateChange, EEnemyState, State, AActor*, Target);

UCLASS()
class OUTBREAK_API AOB_Enemy : public ACharacter
{
	GENERATED_BODY()

public:
	AOB_Enemy();
	
	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = State)
	FOnStateChange OnStateChange;

	UFUNCTION(BlueprintGetter, Category = Components)
	class UOB_HealthComponent* GetHealthComponent() const { return HealthComponent; }

protected:

	/** Properties Component */
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	class USphereComponent* RangeDetectionSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	class USphereComponent* AttackRangeSphere;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadOnly, Category = Components)
	class UOB_HealthComponent* HealthComponent;

	/** Properties Variables */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State)
	TEnumAsByte<EEnemyState> State;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
	float AttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
	TSubclassOf<UDamageType> DmgType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Damage)
	float AttackRate;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Damage)
	//FTimerHandle AttackTimerHandle;
	
	/** Methods Basic */
	
	virtual void BeginPlay() override;

	/** Methods Health */

	UFUNCTION()
	virtual void OnDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	virtual void HandleDeath();

	/** Methods State */

	UFUNCTION(BlueprintCallable, Category = State)
	void SetState(EEnemyState NewState, AActor* Target = nullptr);

	/** Methods AI */

	UFUNCTION()
	virtual void OnRangeDetectionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnRangeDetectionSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	UFUNCTION()
	virtual void OnAttackRangeSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnAttackRangeSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
};
