#include "Pickups/JWWeaponPickUp.h"
#include "Weapon/JWBaseWeapon.h"
#include "Components/JWWeaponComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "JWUtils.h"

void AJWWeaponPickUp::BeginPlay()
{
	Super::BeginPlay();

	PickUpWeapon = GetWorld()->SpawnActor<AJWBaseWeapon>(PickUpWeaponClass);

	WeaponSkeletalMeshComponent = JWUtils::GetComponent<USkeletalMeshComponent>(PickUpWeapon);

	WeaponSkeletalMeshComponent->SetWorldLocation(GetActorLocation());
}

bool AJWWeaponPickUp::GivePickUpTo(APawn* PlayerPawn)
{
	if (!PlayerPawn)
		return false;

	const auto WeaponComponent = JWUtils::GetComponent<UJWWeaponComponent>(PlayerPawn);
	WeaponComponent->EquipWeapon(PickUpWeapon);

	return true;
}