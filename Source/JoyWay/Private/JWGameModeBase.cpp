#include "JWGameModeBase.h"
#include "Player/JWBaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"


AJWGameModeBase::AJWGameModeBase() 
{
	DefaultPawnClass = AJWBaseCharacter::StaticClass();

	FOnPawnDeath.AddUObject(this, &AJWGameModeBase::HandlePawnDeath);
}

void AJWGameModeBase::HandlePawnDeath(AController* Controller)
{
	RespawnPawn(Controller);
}

void AJWGameModeBase::RespawnPawn(AController* Controller)
{
    TArray<AActor*> PlayerStarts;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);

    if (PlayerStarts.Num() > 0)
    {
        APlayerStart* RandomPlayerStart = Cast<APlayerStart>(PlayerStarts[FMath::RandRange(0, PlayerStarts.Num() - 1)]);

        if (RandomPlayerStart)
        {
            FActorSpawnParameters SpawnParams;
            AJWBaseCharacter* NewPawn = GetWorld()->SpawnActor<AJWBaseCharacter>(DefaultPawnClass, RandomPlayerStart->GetActorTransform(), SpawnParams);

            if (Controller)
            {
                Controller->UnPossess();
                Controller->Possess(NewPawn);
            }
        }
    }
}
