#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JWLauncherProjectileActor.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class JOYWAY_API AJWLauncherProjectileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AJWLauncherProjectileActor();

	void SetShotDirection(const FVector& Direction)
	{
		ShotDirection = Direction;
	}

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	float CollisionSphereRadius = 5.0f;

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	UProjectileMovementComponent* MovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float DamageRadius = 200.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float DamageAmount = 50.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	bool DoFullDamage = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float ProjectileLifeTime = 5.0f;

	virtual void BeginPlay() override;

private: 
	FVector ShotDirection;

	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	AController* GetController() const;
};
