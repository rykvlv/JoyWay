#pragma once

#include "CoreMinimal.h"
#include "Weapon/JWBaseWeapon.h"
#include "JWRifleWeapon.generated.h"

UCLASS()
class JOYWAY_API AJWRifleWeapon : public AJWBaseWeapon
{
	GENERATED_BODY()
	
public:	
	virtual void StartFire() override;
	virtual void StopFire() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float TimeBetweenShots = 0.1f;

	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite)
	float WeaponSpread = 1.5f;

	virtual void MakeShot() override;
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;
public:	
	FTimerHandle ShotTimerHandle;
};
