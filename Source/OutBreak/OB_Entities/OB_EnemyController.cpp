// Fill out your copyright notice in the Description page of Project Settings.

#include "OB_Enemy.h"

#include "OB_EnemyController.h"

#include "Navigation/PathFollowingComponent.h"

AOB_EnemyController::AOB_EnemyController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AOB_EnemyController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AOB_EnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TargetActor == nullptr)
	{
		GetPawn()->AddMovementInput(GetPawn()->GetActorForwardVector(), 1.f);
	}
}

void AOB_EnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AOB_Enemy* Enemy = Cast<AOB_Enemy>(InPawn);
	Enemy->OnTargetChange.AddDynamic(this, &AOB_EnemyController::OnTargetChange);
}

void AOB_EnemyController::OnTargetChange(AActor* NewTarget)
{
	TargetActor = NewTarget;
	if (TargetActor == nullptr) return;
	
	auto result = MoveTo(TargetActor->GetActorLocation());
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("MoveTo result: %d"), (int)result));
}

void AOB_EnemyController::OnStateChange(EEnemyState NewState)
{
	if (NewState == EEnemyState::DEAD)
	{
		StopMovement();
	}
}


