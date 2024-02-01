// Fill out your copyright notice in the Description page of Project Settings.


#include "OB_Tile.h"

#include "OutBreak/OB_Items/OB_PickUpItem.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "OutBreak/OB_Entities/OB_Enemy.h"


AOB_Tile::AOB_Tile()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(RootComp);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ArrowComponent->SetupAttachment(RootComponent);

	SpawnZone = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnZone"));
	SpawnZone->SetupAttachment(RootComponent);

	FloorMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMeshComponent"));
	FloorMeshComponent->SetupAttachment(RootComponent);

	LeftWallMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftWallMeshComponent"));
	LeftWallMeshComponent->SetupAttachment(FloorMeshComponent);

	RightWallMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightWallMeshComponent"));
	RightWallMeshComponent->SetupAttachment(FloorMeshComponent);

	TileExitTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TileExitTrigger"));
	TileExitTrigger->SetupAttachment(FloorMeshComponent);

	EnemyKillZone = CreateDefaultSubobject<UBoxComponent>(TEXT("EnemyKillZone"));
	EnemyKillZone->SetupAttachment(RootComponent);
}

FTransform AOB_Tile::GetAttachTransform() const
{
	return ArrowComponent->GetComponentToWorld();
}

TArray<AOB_PickUpItem*> AOB_Tile::GetPickUpItems() const
{
	TArray<AOB_PickUpItem*> Temp;
	for (AActor* SpawnedItem : SpawnedItems)
	{
		AOB_PickUpItem* PickUpItem = Cast<AOB_PickUpItem>(SpawnedItem);
		if (PickUpItem != nullptr)
		{
			Temp.Add(PickUpItem);
		}
	}
	return Temp;
}

void AOB_Tile::BeginPlay()
{
	Super::BeginPlay();

	TileExitTrigger->OnComponentBeginOverlap.AddDynamic(this, &AOB_Tile::OverlapStarted);

	SpawnAllItems();
	SpawnAllEnemies();
}

void AOB_Tile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AOB_Tile::SpawnItem(TSubclassOf<AActor> ItemClass, bool IsPickUp)
{
	FRotator Rotation = FRotator::ZeroRotator;
	FVector Scale = FVector::OneVector;
	if (IsPickUp == false)
	{
		const float RandomRotation = UKismetMathLibrary::RandomFloatInRange(0.0f, 360.0f);
		Rotation = FRotator(RandomRotation, RandomRotation, RandomRotation);

		const float RandomScale = UKismetMathLibrary::RandomFloatInRange(0.5f, 1.5f);
		Scale = FVector(RandomScale, RandomScale, RandomScale);
	}

	const FVector Location = UKismetMathLibrary::RandomPointInBoundingBox(SpawnZone->GetComponentLocation(), SpawnZone->GetScaledBoxExtent());
	const FTransform Transform = FTransform(Rotation, Location, Scale);

	AActor* Spawned = GetWorld()->SpawnActor(ItemClass, &Transform);
	if (Spawned == nullptr) return;
	
	SpawnedItems.Add(Spawned);
}

void AOB_Tile::SpawnAllItems()
{
	for (int32 i = 0; i < NumberOfItemsToSpawn; ++i)
	{
		if (UKismetMathLibrary::RandomBoolWithWeight(ObstacleSpawnProbability) == true)
		{
			const int32 RandomIndex = UKismetMathLibrary::RandomInteger(ObstaclesToSpawn.Num());
			SpawnItem(ObstaclesToSpawn[RandomIndex], false);
		}
		else
		{
			const int32 RandomIndex = UKismetMathLibrary::RandomInteger(PickUpItemsToSpawn.Num());
			SpawnItem(PickUpItemsToSpawn[RandomIndex], true);
		}
	}
}

void AOB_Tile::SpawnAllEnemies()
{
	for (int32 i = 0; i < NumberOfEnemiesToSpawn; ++i)
	{
		SpawnRandomEnemy();
	}
}

void AOB_Tile::SpawnRandomEnemy()
{
	const float RandomWeight = FMath::FRandRange(0.0f, 1.0f);
	float TotalWeight = 0.0f;
	
	TSubclassOf<AOB_Enemy> EnemyClass = nullptr;
	for (auto& [Class, SpawnRate] : EnemiesToSpawn)
	{
		TotalWeight += SpawnRate;
		if (RandomWeight <= TotalWeight)
		{
			EnemyClass = Class;
			break;
		}
	}

	if (EnemyClass == nullptr) return;
	SpawnEnemy(EnemyClass);
}

void AOB_Tile::SpawnEnemy(TSubclassOf<AOB_Enemy> EnemyClass)
{
	const FVector Location = UKismetMathLibrary::RandomPointInBoundingBox(SpawnZone->GetComponentLocation(), SpawnZone->GetScaledBoxExtent());
	const FTransform Transform = FTransform(FRotator::ZeroRotator, Location, FVector::OneVector);

	AActor* Spawned = GetWorld()->SpawnActor(EnemyClass, &Transform);
	//SpawnedItems.Add(Spawned);
}

void AOB_Tile::OverlapStarted_Implementation(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult
)
{
	if (OtherActor != (AActor*)UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)) return;

	OnTileExit.Broadcast();

	FTimerHandle DestroyTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &AOB_Tile::OnTileExitedPendingDestroy, 2.0f, false);
}

void AOB_Tile::OnTileExitedPendingDestroy_Implementation()
{
	for (AActor* SpawnedItem : SpawnedItems)
	{
		SpawnedItem->Destroy();
	}

	TArray<AActor*> OverlappingActors;
	EnemyKillZone->GetOverlappingActors(OverlappingActors, AOB_Enemy::StaticClass());

	for (AActor* OverlappingActor : OverlappingActors)
	{
		if (OverlappingActor != nullptr) OverlappingActor->Destroy();
	}
	
	Destroy();
}


