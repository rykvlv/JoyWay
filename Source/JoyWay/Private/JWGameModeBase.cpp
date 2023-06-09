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
    auto World = GetWorld();
    if (!World || !Controller)
        return;

    auto RandomPlayerStart = GetRandomPlayerStart();
   
    if (!RandomPlayerStart)
        return;
    
    FActorSpawnParameters SpawnParams;
    AJWBaseCharacter* NewPawn = World->SpawnActor<AJWBaseCharacter>(DefaultPawnClass, RandomPlayerStart->GetActorTransform(), SpawnParams);

    Controller->UnPossess();
    Controller->Possess(NewPawn);
}

APlayerStart* AJWGameModeBase::GetRandomPlayerStart() const
{
    auto World = GetWorld();
    if (!World)
        return nullptr;;

    TArray<AActor*> PlayerStarts;
    UGameplayStatics::GetAllActorsOfClass(World, APlayerStart::StaticClass(), PlayerStarts);

    if (PlayerStarts.Num() == 0)
        return nullptr;

    int RandomPlayerStartsIndex = FMath::RandRange(0, PlayerStarts.Num() - 1);
    APlayerStart* RandomPlayerStart = Cast<APlayerStart>(PlayerStarts[RandomPlayerStartsIndex]);

    return RandomPlayerStart;
}
