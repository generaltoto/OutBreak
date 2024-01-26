// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "OB_Enemy.generated.h"

UCLASS()
class OUTBREAK_API AOB_Enemy : public APawn
{
	GENERATED_BODY()

public:
	AOB_Enemy();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
