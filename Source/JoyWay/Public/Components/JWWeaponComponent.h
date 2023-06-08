// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JWWeaponComponent.generated.h"

class AJWBaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JOYWAY_API UJWWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UJWWeaponComponent();

	void StartFire();
	void StopFire();

	void EquipWeapon(AJWBaseWeapon* Weapon);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AJWBaseWeapon> CurrentWeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	AJWBaseWeapon* CurrentWeapon = nullptr;

	AJWBaseWeapon* SpawnWeapon(TSubclassOf<AJWBaseWeapon> WeaponClass);
	
	void AttachWeaponToSocket(AJWBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
};
