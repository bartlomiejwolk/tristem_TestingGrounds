// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "trist_TestingGroundsGameMode.h"
#include "trist_TestingGroundsHUD.h"
#include "trist_TestingGroundsCharacter.h"
#include "UObject/ConstructorHelpers.h"

Atrist_TestingGroundsGameMode::Atrist_TestingGroundsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = Atrist_TestingGroundsHUD::StaticClass();
}
