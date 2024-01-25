// Fill out your copyright notice in the Description page of Project Settings.


#include "OB_Obstacle.h"

#include "OutBreak/OB_Character/OB_Character.h"
#include "Kismet/GameplayStatics.h"
#include "OutBreak/OB_Items/OB_Weapons/TP_WeaponComponent.h"

AOB_Obstacle::AOB_Obstacle()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObstacleMesh"));
	ObstacleMesh->SetupAttachment(RootComponent);
}

void AOB_Obstacle::BeginPlay()
{
	Super::BeginPlay();

	ObstacleMesh->OnComponentHit.AddDynamic(this, &AOB_Obstacle::OnMeshComponentHit);
}

void AOB_Obstacle::OnMeshComponentHit_Implementation(
	UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit
)
{
	const AOB_Character* Character = Cast<AOB_Character>(OtherActor);
	if (Character == nullptr) return;

	//Character->OnDeathDelegate.Broadcast();
}
