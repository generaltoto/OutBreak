// Copyright Epic Games, Inc. All Rights Reserved.

#include "OB_GameMode.h"
#include "OutBreak/OB_Character/OB_Character.h"
#include "UObject/ConstructorHelpers.h"

AOB_GameMode::AOB_GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
