// ProjectZ. All Rights Reserved.


#include "GameMode/PZGameMode.h"

#include "Player/BaseCharacter.h"

APZGameMode::APZGameMode()
{
	DefaultPawnClass = ABaseCharacter::StaticClass();
}
