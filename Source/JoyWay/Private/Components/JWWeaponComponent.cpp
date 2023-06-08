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

	if (CurrentWeaponClass)
	{
		auto Weapon = SpawnWeapon(CurrentWeaponClass);
		EquipWeapon(Weapon);
	}
}


AJWBaseWeapon* UJWWeaponComponent::SpawnWeapon(TSubclassOf<AJWBaseWeapon> WeaponClass)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character || !GetWorld())
		return nullptr;

	auto Weapon = GetWorld()->SpawnActor<AJWBaseWeapon>(WeaponClass);
	Weapon->SetOwner(Character);

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
		Weapon->SetOwner(GetOwner());
		CurrentWeapon = Weapon;
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
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


