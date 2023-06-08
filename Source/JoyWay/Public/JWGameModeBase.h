#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "JWGameModeBase.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FPawnDeathDelegate, AController*);


UCLASS()
class JOYWAY_API AJWGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AJWGameModeBase();

	FPawnDeathDelegate FOnPawnDeath;

private:
	void HandlePawnDeath(AController* Controller);
	void RespawnPawn(AController* Controller);
};
