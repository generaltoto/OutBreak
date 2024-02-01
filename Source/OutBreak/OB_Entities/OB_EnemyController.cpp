// Fill out your copyright notice in the Description page of Project Settings.

#include "OB_EnemyController.h"

#include "OB_Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "OB_Components/OB_HealthComponent.h"

AOB_EnemyController::AOB_EnemyController()
{
	PrimaryActorTick.bCanEverTick = true;
	TargetActor = nullptr;
}

void AOB_EnemyController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AOB_EnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	switch (ControlledPawnState)
	{
		case EEnemyState::IDLE:
			{
				// MoveForward
				GetPawn()->AddMovementInput(ForwardVector, 1.0f);

				// Rotate to the direction of movement
				const FVector MovementDirection = GetPawn()->GetVelocity().GetSafeNormal();
				const FRotator MovementRotation = MovementDirection.Rotation();
				GetPawn()->SetActorRotation(MovementRotation);
				break;
			}
		case EEnemyState::CHASING:
			{
				MoveToActor(TargetActor, AcceptanceRadius);
				break;
			}
		case EEnemyState::ATTACKING:
		case EEnemyState::DEAD:
		default:
			break;
	}
}

void AOB_EnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AOB_Enemy* Enemy = Cast<AOB_Enemy>(InPawn);
	Enemy->GetHealthComponent()->OnDeath.AddDynamic(this, &AOB_EnemyController::OnDeath);
	Enemy->OnStateChange.AddDynamic(this, &AOB_EnemyController::OnStateChange);
}

void AOB_EnemyController::OnStateChange(EEnemyState State, AActor* Target)
{
	TargetActor = Target;
	ControlledPawnState = State;

	UCharacterMovementComponent* MovementComponent = GetCharacter()->GetCharacterMovement();
	switch (State)
	{
		case EEnemyState::IDLE:
			{
				MovementComponent->MaxWalkSpeed = 150.0f;
				break;
			}
		case EEnemyState::CHASING:
			{
				MovementComponent->MaxWalkSpeed = 300.0f;
				break;
			}
		case EEnemyState::ATTACKING:
			{
				MovementComponent->MaxWalkSpeed = 0.0f;
				break;
			}
		case EEnemyState::DEAD:
			{
				MovementComponent->MaxWalkSpeed = 0.0f;
				break;
			}
		default:
			break;
	}
}

void AOB_EnemyController::OnDeath()
{
	StopMovement();
	DetachFromPawn();
}
