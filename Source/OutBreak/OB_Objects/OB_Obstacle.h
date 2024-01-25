// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OB_Obstacle.generated.h"

UCLASS()
class OUTBREAK_API AOB_Obstacle : public AActor
{
	GENERATED_BODY()

public:
	AOB_Obstacle();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Obstacle")
	UStaticMeshComponent* ObstacleMesh;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, Category = "Obstacle")
	void OnMeshComponentHit(
		UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit
	);
};
