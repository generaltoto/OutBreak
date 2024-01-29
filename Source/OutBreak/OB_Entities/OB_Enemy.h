// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "OB_Enemy.generated.h"

UENUM()
enum EEnemyState : uint8
{
	IDLE		UMETA(DisplayName = "Idle"),
	RUNNING 	UMETA(DisplayName = "Running"),
	ATTACKING 	UMETA(DisplayName = "Attacking"),
	DEAD 		UMETA(DisplayName = "Dead")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStateChange, EEnemyState, State);

UCLASS()
class OUTBREAK_API AOB_Enemy : public APawn
{
	GENERATED_BODY()

public:
	AOB_Enemy();

	virtual void Tick(float DeltaTime) override;

protected:

	/** Properties Component */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	class UCapsuleComponent* Capsule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	USkeletalMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	class USphereComponent* RangeDetectionSphere;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadOnly, Category = Components)
	class UOB_HealthComponent* HealthComponent;

	/** Properties Variables */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State)
	TEnumAsByte<EEnemyState> State;

	UPROPERTY(BlueprintAssignable, BlueprintReadWrite, Category = State)
	FOnStateChange OnStateChange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Target)
	AActor* TargetActor;
	
	/** Methods Basic */
	
	virtual void BeginPlay() override;

	/** Methods Health */

	UFUNCTION()
	virtual void OnDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	virtual void HandleDeath();

	/** Methods State */

	UFUNCTION(BlueprintCallable, Category = State)
	void SetState(EEnemyState NewState);

	/** Methods AI */

	UFUNCTION()
	virtual void OnRangeDetectionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnRangeDetectionSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);
};
