#pragma once

#include "CoreMinimal.h"
#include "Weapon/JWBaseWeapon.h"
#include "JWLauncherWeapon.generated.h"

class AJWLauncherProjectileActor;

UCLASS()
class JOYWAY_API AJWLauncherWeapon : public AJWBaseWeapon
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AJWLauncherProjectileActor> ProjectileClass;

	virtual void MakeShot() override;
};
