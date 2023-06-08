#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JWBaseWeapon.generated.h"

class USkeletalMeshComponent;
class APlayerController;

UCLASS()
class JOYWAY_API AJWBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AJWBaseWeapon();

	virtual void StartFire();
	virtual void StopFire();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	USkeletalMeshComponent* WeaponMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	float TraceMaxDistance = 1500.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	float DamageAmount = 10.0f;

	virtual void MakeShot();
	virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	APlayerController* GetPlayerController() const;
	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
	FVector GetMuzzleWorldLocation() const;
	void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const;
	void MakeDamage(const FHitResult& HitResult);

	virtual void BeginPlay() override;


};
