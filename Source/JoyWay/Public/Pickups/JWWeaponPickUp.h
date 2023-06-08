#pragma once

#include "CoreMinimal.h"
#include "Pickups/JWBasePickUp.h"
#include "JWWeaponPickUp.generated.h"

class AJWBaseWeapon;
class USkeletalMeshComponent;

UCLASS()
class JOYWAY_API AJWWeaponPickUp : public AJWBasePickUp
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AJWBaseWeapon> PickUpWeaponClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	USkeletalMeshComponent* WeaponSkeletalMeshComponent;

private:
	AJWBaseWeapon* PickUpWeapon;

	virtual bool GivePickUpTo(APawn* PlayerPawn) override;
};
