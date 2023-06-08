#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JWBasePickUp.generated.h"

class USphereComponent;
class AJWBaseCharacter;

UCLASS()
class JOYWAY_API AJWBasePickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	AJWBasePickUp();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Pickup")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Pickup")
	float CollisionRadius = 50.0f;
	
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
public:	
	virtual void Tick(float DeltaTime) override;

private:
	virtual bool GivePickUpTo(APawn* PlayerPawn);

	void PickUpWasTaken();
};
