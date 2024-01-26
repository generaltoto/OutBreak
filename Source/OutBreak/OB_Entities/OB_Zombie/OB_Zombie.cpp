// Fill out your copyright notice in the Description page of Project Settings.

#include "OB_Zombie.h"

#include "Components/CapsuleComponent.h"

AOB_Zombie::AOB_Zombie()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AOB_Zombie::BeginPlay()
{
	Super::BeginPlay();
	
}

void AOB_Zombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
