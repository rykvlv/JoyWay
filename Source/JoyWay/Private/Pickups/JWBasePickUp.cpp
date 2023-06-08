#include "Pickups/JWBasePickUp.h"
#include "Components/SphereComponent.h"
#include "Player/JWBaseCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickUp, All, All);

AJWBasePickUp::AJWBasePickUp()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	CollisionComponent->InitSphereRadius(CollisionRadius);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(CollisionComponent);
}

void AJWBasePickUp::BeginPlay()
{
	Super::BeginPlay();
	
	check(CollisionComponent);
}

void AJWBasePickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJWBasePickUp::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const auto Pawn = Cast<APawn>(OtherActor);
	if (GivePickUpTo(Pawn))
	{
		PickUpWasTaken();
	}
}

bool AJWBasePickUp::GivePickUpTo(APawn* PlayerPawn)
{
	return false;
}

void AJWBasePickUp::PickUpWasTaken()
{
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	Destroy();
}