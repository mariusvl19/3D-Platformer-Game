// Copyright Epic Games, Inc. All Rights Reserved.

#include "WS4GameMode.h"
#include "WS4Character.h"
#include "UObject/ConstructorHelpers.h"

AWS4GameMode::AWS4GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
