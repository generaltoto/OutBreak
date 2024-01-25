// Fill out your copyright notice in the Description page of Project Settings.


#include "OB_PickUpItem.h"

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AOB_PickUpItem::AOB_PickUpItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	//SetRootComponent(StaticMeshComponent);
	
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->InitSphereRadius(50.0f);
	SphereComponent->SetupAttachment(StaticMeshComponent);
}

// Called when the game starts or when spawned
void AOB_PickUpItem::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AOB_PickUpItem::OverlapStarted);
}

void AOB_PickUpItem::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Rotate the item
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += DeltaSeconds * 100.0f;
	SetActorRotation(NewRotation);
}

void AOB_PickUpItem::OverlapStarted_Implementation(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult
)
{
	OnPickUpItem.Broadcast();

	UGameplayStatics::PlaySoundAtLocation(this, PickUpSound, GetActorLocation());

	Destroy();
}


