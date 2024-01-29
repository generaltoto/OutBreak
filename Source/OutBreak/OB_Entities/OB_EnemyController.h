// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "OB_EnemyController.generated.h"

UCLASS()
class OUTBREAK_API AOB_EnemyController : public AAIController
{
	GENERATED_BODY()

public:
	AOB_EnemyController();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void OnPossess(APawn* InPawn) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Target)
	AActor* TargetActor;

	UFUNCTION()
	void OnTargetChange(AActor* NewTarget);

	UFUNCTION()
	void OnStateChange(EEnemyState NewState);

	
};
