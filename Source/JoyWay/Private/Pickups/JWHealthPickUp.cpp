// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/JWHealthPickUp.h"
#include "Player/JWBaseCharacter.h"
#include "Components/JWHealthComponent.h"
#include "JWUtils.h"

bool AJWHealthPickUp::GivePickUpTo(APawn* PlayerPawn)
{
	if (!PlayerPawn)
		return false;

	const auto HealthComponent = JWUtils::GetComponent<UJWHealthComponent>(PlayerPawn);
	if (!HealthComponent)
		return false;

	return HealthComponent->TryToAddHealth(BonusHealthAmount);
}