// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ShooterGameMode.h"
#include "../UI/ShooterHUD.h"
#include "../Actors/ShooterCharacter.h"
#include "UObject/ConstructorHelpers.h"

AShooterGameMode::AShooterGameMode(): Super() {
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Character/bpShooterCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AShooterHUD::StaticClass();
}
