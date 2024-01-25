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

	UPROPERTY(EditAnywhere, Category = "Tile Events")
	int32 NumberOfItemsToSpawn;

	UPROPERTY(EditAnywhere, Category = "Tile Events")
	float ObstacleSpawnProbability;

	UPROPERTY(EditAnywhere, Category = "Tile Events")
	TArray<TSubclassOf<AActor>> ObstaclesToSpawn;
	
	UPROPERTY(EditAnywhere, Category = "Tile Events")
	TArray<TSubclassOf<AActor>> PickUpItemsToSpawn;

	UPROPERTY(VisibleAnywhere, Category = "Tile Components")
	TArray<AActor*> SpawnedItems;

	UPROPERTY(BlueprintAssignable, Category = "Tile Events")
	FOnTileExitDelegate OnTileExit;

	UPROPERTY(EditAnywhere, Category = "Tile Components")
	UArrowComponent* ArrowComponent;

	UPROPERTY(EditAnywhere, Category = "Tile Components")
	UStaticMeshComponent* FloorMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Tile Components")
	UStaticMeshComponent* LeftWallMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Tile Components")
	UStaticMeshComponent* RightWallMeshComponent;

	UPROPERTY(EditAnywhere, Category = "Tile Triggers")
	UBoxComponent* TileExitTrigger;

	UFUNCTION(BlueprintNativeEvent, Category = "Tile Triggers")
	void OverlapStarted(
		UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION(BlueprintNativeEvent, Category = "Tile Events")
	void OnTileExitedPendingDestroy();

	UPROPERTY(EditAnywhere, Category = "Tile Triggers")
	UBoxComponent* SpawnZone;

	UFUNCTION(BlueprintCallable, Category = "Tile Events")
	FTransform GetAttachTransform() const;

	UFUNCTION(BlueprintCallable, Category = "Tile Items")
	TArray<AOB_PickUpItem*> GetPickUpItems() const;

protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(Blueprintable, Category = "Tile Events")
	void SpawnItem(TSubclassOf<AActor> ItemClass, bool IsPickUp = false);

	UFUNCTION(Blueprintable, Category = "Tile Events")
	void SpawnAllItems();
};
