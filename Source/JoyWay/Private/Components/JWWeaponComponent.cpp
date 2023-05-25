#include "Components/JWWeaponComponent.h"
#include "Weapon/JWBaseWeapon.h"
#include "GameFramework/Character.h"

#include <algorithm>

UJWWeaponComponent::UJWWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UJWWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapons();
}

void UJWWeaponComponent::SpawnWeapons() 
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character)
		return;

	if (CurrentWeaponClass)
	{
		auto Weapon = SpawnWeapon(CurrentWeaponClass);
		if (Weapon)
		{
			Weapon->SetOwner(Character);
			AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponEquipSocketName);
		}
	}

	if (PreviousWeaponClass)
	{
		auto Weapon = SpawnWeapon(PreviousWeaponClass);
		if (Weapon)
		{
			Weapon->SetOwner(Character);
			AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
		}
	}
}

AJWBaseWeapon* UJWWeaponComponent::SpawnWeapon(TSubclassOf<AJWBaseWeapon> WeaponClass)
{
	if (!GetWorld())
		return nullptr;

	auto Weapon = GetWorld()->SpawnActor<AJWBaseWeapon>(WeaponClass);

	return Weapon;
}

void UJWWeaponComponent::AttachWeaponToSocket(AJWBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName) 
{
	if (!Weapon || !SceneComponent)
		return;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void UJWWeaponComponent::EquipWeapon(AJWBaseWeapon* Weapon)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character)
		return;

	if (Weapon)
	{
		CurrentWeapon = Weapon;
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
	}
}

void UJWWeaponComponent::StartFire()
{
	if (!CurrentWeapon)
		return;

	CurrentWeapon->StartFire();
}

void UJWWeaponComponent::StopFire()
{
	if (!CurrentWeapon)
		return;

	CurrentWeapon->StopFire();
}

void UJWWeaponComponent::NextWeapon()
{
	EquipWeapon(PreviousWeapon);
	std::swap(CurrentWeapon, PreviousWeapon);
}



