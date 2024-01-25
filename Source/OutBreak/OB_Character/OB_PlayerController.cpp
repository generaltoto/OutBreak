// Copyright Epic Games, Inc. All Rights Reserved.


#include "OB_PlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "OB_Character.h"

void AOB_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	CharacterRef = Cast<AOB_Character>(GetPawn());

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}
}

void AOB_PlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Add forward movement input
	CharacterRef->AddMovementInput(ForwardVector, 1.f);
}

void AOB_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AOB_PlayerController::OnJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AOB_PlayerController::OnStopJump);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AOB_PlayerController::OnMove);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AOB_PlayerController::OnLook);
	}
}

void AOB_PlayerController::OnJump(const FInputActionValue& Value)
{
	CharacterRef->Jump();
}

void AOB_PlayerController::OnStopJump(const FInputActionValue& Value)
{
	CharacterRef->StopJumping();
}

void AOB_PlayerController::OnMove(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	CharacterRef->AddMovementInput(RightVector, MovementVector.X);
}

void AOB_PlayerController::OnLook(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	FRotator NewRotation = CharacterRef->GetControlRotation() + FRotator((LookAxisVector.Y * LookSensitivity), (LookAxisVector.X * LookSensitivity), 0.0f);

	NewRotation.Yaw = FMath::Clamp(NewRotation.Yaw, -LookAngle, LookAngle);

	SetControlRotation(NewRotation);
}
