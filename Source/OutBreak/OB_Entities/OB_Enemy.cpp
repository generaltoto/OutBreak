// Fill out your copyright notice in the Description page of Project Settings.

#include "OB_Enemy.h"

#include "Components/CapsuleComponent.h"
#include "OB_Components/OB_HealthComponent.h"

AOB_Enemy::AOB_Enemy()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SetRootComponent(Capsule);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	HealthComponent = CreateDefaultSubobject<UOB_HealthComponent>(TEXT("HealthComponent"));
}

void AOB_Enemy::BeginPlay()
{
	Super::BeginPlay();

	OnTakeAnyDamage.AddDynamic(this, &AOB_Enemy::OnDamageTaken);
}

void AOB_Enemy::OnDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
}

void AOB_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


