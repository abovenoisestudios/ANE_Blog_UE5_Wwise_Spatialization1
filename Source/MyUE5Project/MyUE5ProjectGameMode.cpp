// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyUE5ProjectGameMode.h"
#include "MyUE5ProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMyUE5ProjectGameMode::AMyUE5ProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
