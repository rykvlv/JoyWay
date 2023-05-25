// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/JWBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"

AJWBaseCharacter::AJWBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void AJWBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AJWBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJWBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AJWBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AJWBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AJWBaseCharacter::LookUp);
	PlayerInputComponent->BindAxis("TurnAround", this, &AJWBaseCharacter::TurnAround);
}

void AJWBaseCharacter::MoveForward(float Amount) 
{
	AddMovementInput(GetActorForwardVector(), Amount);
}

void AJWBaseCharacter::MoveRight(float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
}

void AJWBaseCharacter::LookUp(float Amount)
{
	AddControllerPitchInput(Amount);
}

void AJWBaseCharacter::TurnAround(float Amount)
{
	AddControllerYawInput(Amount);
}

float AJWBaseCharacter::GetMovementDirection() const
{
	if (GetVelocity().IsZero())
		return 0.0f;

	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);

	return FMath::RadiansToDegrees(AngleBetween) * FMath::Sign(CrossProduct.Z);
}

