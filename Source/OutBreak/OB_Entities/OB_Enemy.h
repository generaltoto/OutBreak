// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "OB_Enemy.generated.h"

UENUM()
enum EMyEnum
{
	IDLE,
	RUNNING,
	ATTACKING,
	DEAD
};

UCLASS()
class OUTBREAK_API AOB_Enemy : public APawn
{
	GENERATED_BODY()

public:
	AOB_Enemy();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	class UCapsuleComponent* Capsule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	USkeletalMeshComponent* Mesh;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	class UOB_HealthComponent* HealthComponent;
	
	virtual void BeginPlay() override;

	virtual void OnDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

public:
	virtual void Tick(float DeltaTime) override;
};
