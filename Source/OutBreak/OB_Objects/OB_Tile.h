// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OB_Tile.generated.h"

class AOB_PickUpItem;
class UBoxComponent;
class UArrowComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTileExitDelegate);

UCLASS()
class OUTBREAK_API AOB_Tile : public AActor
{
	GENERATED_BODY()

public:
	AOB_Tile();

	/** Obstacles and PickUp Items */

	UFUNCTION(BlueprintCallable, Category = "Obstacles and PickUp Items")
	TArray<AOB_PickUpItem*> GetPickUpItems() const;

	/** Tile Events */

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnTileExitDelegate OnTileExit;

	/** Components */

	UFUNCTION(BlueprintCallable, Category = "Components")
	FTransform GetAttachTransform() const;

protected:
	
	/** Obstacles and PickUp Items */
	
	UPROPERTY(EditAnywhere, Category = "Obstacles and PickUp Items", meta = (ClampMin = 0))
	int32 NumberOfItemsToSpawn;

	UPROPERTY(EditAnywhere, Category = "Obstacles and PickUp Items", meta = (ClampMin = 0.0f, ClampMax = 1.0f))
	float ObstacleSpawnProbability;

	UPROPERTY(EditAnywhere, Category = "Obstacles and PickUp Items")
	TArray<TSubclassOf<AActor>> ObstaclesToSpawn;
	
	UPROPERTY(EditAnywhere, Category = "Obstacles and PickUp Items")
	TArray<TSubclassOf<AActor>> PickUpItemsToSpawn;

	UPROPERTY(VisibleAnywhere, Category = "Obstacles and PickUp Items")
	TArray<AActor*> SpawnedItems;

	UFUNCTION(Blueprintable, Category = "Obstacles and PickUp Items")
	void SpawnItem(TSubclassOf<AActor> ItemClass, bool IsPickUp = false);

	UFUNCTION(Blueprintable, Category = "Obstacles and PickUp Items")
	void SpawnAllItems();

	/** Enemies */

	UPROPERTY(EditAnywhere, Category = "Enemies", meta = (ClampMin = 0, ClampMax = 10))
	int32 NumberOfEnemiesToSpawn;

	UPROPERTY(EditAnywhere, Category = "Enemies")
	TMap<TSubclassOf<class AOB_Enemy>, float> EnemiesToSpawn;

	UPROPERTY(EditAnywhere, Category = "Enemies")
	UBoxComponent* EnemyKillZone;

	UFUNCTION(BlueprintCallable, Category = "Enemies")
	void SpawnAllEnemies();

	UFUNCTION(Blueprintable, Category = "Enemies")
	void SpawnRandomEnemy();

	UFUNCTION(Blueprintable, Category = "Enemies")
	void SpawnEnemy(TSubclassOf<class AOB_Enemy> EnemyClass);

	/** Tile Events */
	
	UFUNCTION(BlueprintNativeEvent, Category = "Events")
	void OverlapStarted(
		UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION(BlueprintNativeEvent, Category = "Events")
	void OnTileExitedPendingDestroy();
	
	/** Tile Components */

	UPROPERTY(EditAnywhere, Category = "Components")
	UArrowComponent* ArrowComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* FloorMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* LeftWallMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* RightWallMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	UBoxComponent* TileExitTrigger;
	
	UPROPERTY(EditAnywhere, Category = "Components")
	UBoxComponent* SpawnZone;
	
	/** Tile Basics */
	
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;
};
