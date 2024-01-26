// Fill out your copyright notice in the Description page of Project Settings.

#include "OB_Enemy.h"

AOB_Enemy::AOB_Enemy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AOB_Enemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void AOB_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


