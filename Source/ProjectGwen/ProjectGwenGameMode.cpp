// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectGwenGameMode.h"
#include "ProjectGwenCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjectGwenGameMode::AProjectGwenGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
