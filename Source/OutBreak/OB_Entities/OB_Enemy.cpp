// Fill out your copyright notice in the Description page of Project Settings.

#include "OB_Enemy.h"

#include "OB_EnemyController.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "OB_Components/OB_HealthComponent.h"

AOB_Enemy::AOB_Enemy()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UOB_HealthComponent>(TEXT("HealthComponent"));

	RangeDetectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("RangeDetectionSphere"));
	RangeDetectionSphere->SetupAttachment(RootComponent);

	AttackRangeSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AttackRangeSphere"));
	AttackRangeSphere->SetupAttachment(RootComponent);
}

void AOB_Enemy::BeginPlay()
{
	Super::BeginPlay();
	
	RangeDetectionSphere->OnComponentBeginOverlap.AddDynamic(this, &AOB_Enemy::OnRangeDetectionSphereBeginOverlap);
	RangeDetectionSphere->OnComponentEndOverlap.AddDynamic(this, &AOB_Enemy::OnRangeDetectionSphereEndOverlap);

	AttackRangeSphere->OnComponentBeginOverlap.AddDynamic(this, &AOB_Enemy::OnAttackRangeSphereBeginOverlap);
	AttackRangeSphere->OnComponentEndOverlap.AddDynamic(this, &AOB_Enemy::OnAttackRangeSphereEndOverlap);

	OnTakeAnyDamage.AddDynamic(this, &AOB_Enemy::OnDamageTaken);
	HealthComponent->OnDeath.AddDynamic(this, &AOB_Enemy::HandleDeath);

	SetState(IDLE);
}

void AOB_Enemy::OnDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	HealthComponent->RemoveHealth(Damage);
}

void AOB_Enemy::HandleDeath()
{
	SetActorEnableCollision(false);

	SetState(DEAD);
	
	FTimerHandle DeathTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeathTimerHandle, [this]()
	{
		Destroy();
	}, 1.0f, false);
}

void AOB_Enemy::SetState(EEnemyState NewState, AActor* Target)
{
	State = NewState;
	OnStateChange.Broadcast(State, Target);
}

void AOB_Enemy::OnRangeDetectionSphereBeginOverlap(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult
)
{
	if (OtherActor->ActorHasTag("Player") == false) return;
	
	SetState(CHASING, OtherActor);
}

void AOB_Enemy::OnRangeDetectionSphereEndOverlap(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex
)
{
	if (OtherActor->ActorHasTag("Player") == false) return;

	SetState(IDLE);
}

void AOB_Enemy::OnAttackRangeSphereBeginOverlap(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult
)
{
	if (OtherActor->ActorHasTag("Player") == false) return;
	
	SetState(ATTACKING, OtherActor);

	UGameplayStatics::ApplyDamage(OtherActor, AttackDamage, GetController(), this, DmgType);
	
	// GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, [this, OtherActor]()
	// {
	// 	if (OtherActor == nullptr)
	// 	{
	// 		GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandle);
	// 		return;
	// 	}
	// 	
	// }, AttackRate, true);
}

void AOB_Enemy::OnAttackRangeSphereEndOverlap(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex
)
{
	if (OtherActor->ActorHasTag("Player") == false) return;
	
	SetState(CHASING, OtherActor);

	// GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandle);
}
