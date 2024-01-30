#pragma once

#include "OB_EnemyStates.generated.h"

UENUM(BlueprintType)
enum EEnemyState : uint8
{
	IDLE		UMETA(DisplayName = "Idle"),
	CHASING 	UMETA(DisplayName = "Chasing"),
	ATTACKING 	UMETA(DisplayName = "Attacking"),
	DEAD 		UMETA(DisplayName = "Dead")
};