// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OB_PlayerController.generated.h"

struct FInputActionValue;
class UInputAction;
class AOB_Character;
class UInputMappingContext;

UCLASS()
class OUTBREAK_API AOB_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupInputComponent() override;

	void OnJump(const FInputActionValue& Value);
	void OnStopJump(const FInputActionValue& Value);

	void OnMove(const FInputActionValue& Value);

	void OnLook(const FInputActionValue& Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Refs)
	AOB_Character* CharacterRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	FVector ForwardVector = FVector(1.0f, 0.0f, 0.0f);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	FVector RightVector = FVector(0.0f, 1.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta=(UIMin = 30.0, UIMax = 120.0))
	float LookAngle = 90.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta=(UIMin = 0.01, UIMax = 10.0))
	float LookSensitivity = 1.0f;
};
