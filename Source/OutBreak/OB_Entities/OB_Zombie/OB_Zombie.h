// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OutBreak/OB_Entities/OB_Enemy.h"
#include "OB_Zombie.generated.h"

UCLASS()
class OUTBREAK_API AOB_Zombie : public AOB_Enemy
{
	GENERATED_BODY()

public:
	AOB_Zombie();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
