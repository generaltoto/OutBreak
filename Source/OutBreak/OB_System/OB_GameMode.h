// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OB_GameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTileSpawned, class AOB_Tile*, SpawnedTile);

UCLASS(minimalapi)
class AOB_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AOB_GameMode();

	UPROPERTY(BlueprintAssignable, Category = Tile)
	FOnTileSpawned OnTileSpawned;

protected:

	virtual void BeginPlay() override;

	/** Tile */

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Tile)
	TArray<TSubclassOf<class AOB_Tile>> TileClasses;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Tile)
	FTransform NextTileTransform;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Tile, meta = (ClampMin = 1, ClampMax = 10))
	int InitialTileCount;

	UFUNCTION(BlueprintCallable, Category = Tile)
	void SpawnRandomTile();

	UFUNCTION(BlueprintCallable, Category = Tile)
	void SpawnTile(TSubclassOf<class AOB_Tile> TileClass);

	UFUNCTION(BlueprintCallable, Category = Tile)
	TSubclassOf<class AOB_Tile> GetRandomTileClass();
	
	/** Navigation */
	
	UFUNCTION(BlueprintImplementableEvent, Category = Navigation)
	void UpdateNavigationBounds();
	
};



