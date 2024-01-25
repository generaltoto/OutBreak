// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OB_PickUpItem.generated.h"

class USphereComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPickUpItemDelegate);

UCLASS()
class OUTBREAK_API AOB_PickUpItem : public AActor
{
	GENERATED_BODY()

public:
	AOB_PickUpItem();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:

	UPROPERTY(BlueprintAssignable, Category = "PickUpItem")
	FPickUpItemDelegate OnPickUpItem;

	UPROPERTY(EditAnywhere, Category = "PickUpItem")
	USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, Category = "PickUpItem")
	USoundBase* PickUpSound;

	UPROPERTY(EditAnywhere, Category = "PickUpItem")
	UStaticMeshComponent* StaticMeshComponent;
	
	UFUNCTION(BlueprintNativeEvent, Category = "PickUpItem")
	void OverlapStarted(
		UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult
	);
};
