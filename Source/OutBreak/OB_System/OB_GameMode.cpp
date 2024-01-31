// Copyright Epic Games, Inc. All Rights Reserved.

#include "OB_GameMode.h"

#include "Kismet/KismetMathLibrary.h"
#include "OutBreak/OB_Objects/OB_Tile.h"
#include "UObject/ConstructorHelpers.h"

AOB_GameMode::AOB_GameMode()
	: Super()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	InitialTileCount = 3;
}

void AOB_GameMode::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < InitialTileCount; i++)
	{
		SpawnRandomTile();
	}
}

void AOB_GameMode::SpawnRandomTile()
{
	const TSubclassOf<AOB_Tile> RandomTileClass = GetRandomTileClass();
	SpawnTile(RandomTileClass);

	UpdateNavigationBounds();
}

void AOB_GameMode::SpawnTile(TSubclassOf<AOB_Tile> TileClass)
{
	if (TileClass == nullptr) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AOB_Tile* SpawnedTile = GetWorld()->SpawnActor<AOB_Tile>(TileClass, NextTileTransform, SpawnParams);
	if (SpawnedTile == nullptr) return;

	SpawnedTile->OnTileExit.AddDynamic(this, &AOB_GameMode::SpawnRandomTile);
	NextTileTransform = SpawnedTile->GetAttachTransform();
	OnTileSpawned.Broadcast(SpawnedTile);
}

TSubclassOf<AOB_Tile> AOB_GameMode::GetRandomTileClass()
{
	return TileClasses[UKismetMathLibrary::RandomIntegerInRange(0, TileClasses.Num() - 1)];
}
