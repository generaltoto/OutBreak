// Fill out your copyright notice in the Description page of Project Settings.

#include "OB_Enemy.h"

#include "OB_EnemyController.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "OB_Components/OB_HealthComponent.h"

AOB_Enemy::AOB_Enemy()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	SetRootComponent(Capsule);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	HealthComponent = CreateDefaultSubobject<UOB_HealthComponent>(TEXT("HealthComponent"));

	RangeDetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("RangeDetectionSphere"));
	RangeDetectionSphere->SetupAttachment(RootComponent);
}

void AOB_Enemy::BeginPlay()
{
	Super::BeginPlay();
	
	RangeDetectionSphere->OnComponentBeginOverlap.AddDynamic(this, &AOB_Enemy::OnRangeDetectionSphereBeginOverlap);
	RangeDetectionSphere->OnComponentEndOverlap.AddDynamic(this, &AOB_Enemy::OnRangeDetectionSphereEndOverlap);

	OnTakeAnyDamage.AddDynamic(this, &AOB_Enemy::OnDamageTaken);
	HealthComponent->OnDeath.AddDynamic(this, &AOB_Enemy::HandleDeath);
}

void AOB_Enemy::OnDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	HealthComponent->RemoveHealth(Damage);
}

void AOB_Enemy::HandleDeath()
{
	Destroy();
}

void AOB_Enemy::SetState(EEnemyState NewState)
{
	State = NewState;
	OnStateChange.Broadcast(State);
}

void AOB_Enemy::OnRangeDetectionSphereBeginOverlap(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult
)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OnRangeDetectionSphereBeginOverlap"));
	
	if (OtherActor->ActorHasTag("Player") == false) return;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OnRangeDetectionSphereBeginOverlap Player"));

	OnTargetChange.Broadcast(OtherActor);
}

void AOB_Enemy::OnRangeDetectionSphereEndOverlap(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex
)
{
	if (OtherActor->ActorHasTag("Player") == false) return;

	OnTargetChange.Broadcast(nullptr);
}

void AOB_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


