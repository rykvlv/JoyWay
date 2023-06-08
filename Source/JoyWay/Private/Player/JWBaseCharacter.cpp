// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/JWBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/JWWeaponComponent.h"
#include "Components/JWHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/GameModeBase.h"
#include "JWGameModeBase.h"


AJWBaseCharacter::AJWBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	WeaponComponent = CreateDefaultSubobject<UJWWeaponComponent>("WeaponComponent");

	HealthComponent = CreateDefaultSubobject<UJWHealthComponent>("HealthComponent");
	
	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
	HealthTextComponent->SetupAttachment(GetRootComponent());
}

void AJWBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	check(HealthComponent);
	check(WeaponComponent);

	OnHealthChanged(HealthComponent->GetHealth());
	HealthComponent->OnDeath.AddUObject(this, &AJWBaseCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &AJWBaseCharacter::OnHealthChanged);
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
	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UJWWeaponComponent::StartFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UJWWeaponComponent::StopFire);
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

void AJWBaseCharacter::OnDeath()
{
	PlayAnimMontage(DeathAnimMontage);
	GetCharacterMovement()->DisableMovement();

	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	HealthTextComponent->SetVisibility(false);

	AJWGameModeBase* GameMode = Cast<AJWGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->FOnPawnDeath.Broadcast(Controller);
	}
	SetLifeSpan(TimeToDestroy);
}


void AJWBaseCharacter::OnHealthChanged(float Health)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}