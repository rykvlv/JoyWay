// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/JWBasePickUp.h"
#include "JWHealthPickUp.generated.h"


class AJWBaseCharacter;

UCLASS()
class JOYWAY_API AJWHealthPickUp : public AJWBasePickUp
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthPickUp")
	float BonusHealthAmount = 25.0f;

private:
	virtual bool GivePickUpTo(APawn* PlayerPawn) override;
};
