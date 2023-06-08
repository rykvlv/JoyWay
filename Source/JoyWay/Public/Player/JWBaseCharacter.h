// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "JWBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UJWWeaponComponent;
class UJWHealthComponent;
class UTextRenderComponent;

UCLASS()
class JOYWAY_API AJWBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AJWBaseCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UJWWeaponComponent* WeaponComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UJWHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UTextRenderComponent* HealthTextComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathAnimMontage = nullptr;

	UPROPERTY(EditDefaulsOnly, BlueprintReadWrite, Category = "Character")
	float TimeToDestroy = 5.0f;

	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UJWHealthComponent* GetHealthComponent() { return HealthComponent; }

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetMovementDirection() const;

private:
	void MoveForward(float Amount);
	void MoveRight(float Amount);

	void LookUp(float Amount);
	void TurnAround(float Amount);

	void OnDeath();
	void OnRespawn();
	void OnHealthChanged(float Health);
};
